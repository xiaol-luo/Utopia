using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;
using Utopia.UI;

namespace Utopia
{
    public class Core
    {
        public static Core instance { get { return m_instance; } }
        protected static Core m_instance = null;
        public static void MakeInstance(MonoBehaviour _owner)
        {
            if (null == m_instance)
                m_instance = new Core(_owner);
            else
                Debug.LogError("NewApp is single instance, can only make one instance");
        }

        public LogModule logModule
        {
            get
            {
                return m_modules[CoreModule.EModule.LogModule] as LogModule;
            }
        }

        public DateTimeModule datetimeModule
        {
            get
            {
                return m_modules[CoreModule.EModule.DateTimeModule] as DateTimeModule;
            }
        }

        public TimerModule timerModule
        {
            get
            {
                return m_modules[CoreModule.EModule.TimerModule] as TimerModule;
            }
        }
        public EventModule eventModule
        {
            get
            {
                return m_modules[CoreModule.EModule.EventModule] as EventModule;
            }
        }
        public NetModule netModule
        {
            get
            {
                return m_modules[CoreModule.EModule.NetModule] as NetModule;
            }
        }

        public UIPanelMgr panelMgr
        {
            get
            {
                UIModule uiModule = m_modules[CoreModule.EModule.UIModule] as UIModule;
                return uiModule.panelMgr;
            }
        }


        public MonoBehaviour root { get; protected set; }

        public CoreModule.EStage moduleStage { get; protected set; }

        const int EModuleCount = (int)CoreModule.EModule.Count;
        CoreModule[] m_modules = new CoreModule[EModuleCount];

        public void ForeachModule(System.Action<CoreModule> _fn)
        {
            System.Action<CoreModule, object, object> fn = (CoreModule module, object p1, object p2) => { _fn(module); };
            foreach (CoreModule module in m_modules)
            {
                fn(module, null, null);
            }
        }
        public void ForeachModule(System.Action<CoreModule, object, object> fn, object inParam, ref object outParam)
        {
            foreach (CoreModule module in m_modules)
            {
                fn(module, inParam, outParam);
            }
        }
        bool ExecuteStageFnUtil(CoreModule.EStage preStage, CoreModule.EStage fromStage, CoreModule.EStage toStage)
        {
            this.moduleStage = fromStage;

            bool allModuleStageMatch = true;
            ForeachModule((CoreModule module) =>
            {
                if (CoreModule.EStage.Releasing !=  fromStage)
                    allModuleStageMatch &= (module.stage == preStage);
            });
            if (!allModuleStageMatch)
                return false;

            ForeachModule((CoreModule module) =>
            {
                module.stage = fromStage;
            });

            int failModuleId = CoreModule.EModule.Count;
            while (true)
            {
                bool allReady = true;
                foreach (CoreModule module in m_modules)
                {
                    if (toStage == module.stage)
                        continue;

                    CoreModule.ERet ret = CoreModule.ERet.Fail;
                    switch(fromStage)
                    {
                        case CoreModule.EStage.Awaking:
                            {
                                ret = module.Awake();
                            }
                            break;
                        case CoreModule.EStage.Staring:
                            {
                                ret = module.Start();
                            }
                            break;
                        case CoreModule.EStage.Releasing:
                            {
                                ret = module.Release();
                            }
                            break;
                    }
                    if (CoreModule.ERet.Fail == ret)
                    {
                        failModuleId = module.moduleId;
                        break;
                    }
                    if (toStage != module.stage)
                        allReady = false;
                }
                if (failModuleId != CoreModule.EModule.Count)
                {
                    Debug.LogFormat("AppModule {0} try from {1} to {2} ", fromStage, toStage, failModuleId);
                    break;
                }
                if (allReady)
                    break;
            }
            bool returnVal= CoreModule.EModule.Count == failModuleId;
            if (returnVal)
                this.moduleStage = toStage;
            return returnVal;
        }
        protected Core(MonoBehaviour _root)
        {
            root = _root;

            LayerUtil.Init();

            m_modules[CoreModule.EModule.UIModule] = new UIModule(this);
            m_modules[CoreModule.EModule.CameraModule] = new CameraModule(this);
            m_modules[CoreModule.EModule.DateTimeModule] = new DateTimeModule(this);
            m_modules[CoreModule.EModule.TimerModule] = new TimerModule(this);
            m_modules[CoreModule.EModule.LogModule] = new LogModule(this);
            m_modules[CoreModule.EModule.EventModule] = new EventModule(this);
            m_modules[CoreModule.EModule.NetModule] = new NetModule(this);
            m_modules[CoreModule.EModule.ResourceModule] = new ResourceModule(this);

            moduleStage = CoreModule.EStage.Free;
            ForeachModule((CoreModule module) => {
                module.Init();
            });
            moduleStage = CoreModule.EStage.Inited;
        }



        public void Awake()
        {
            bool ret = ExecuteStageFnUtil(CoreModule.EStage.Inited, CoreModule.EStage.Awaking, CoreModule.EStage.Awaked);
            if (!ret)
                this.Quit();
        }
        public void Start()
        {
            bool ret = ExecuteStageFnUtil(CoreModule.EStage.Awaked, CoreModule.EStage.Staring, CoreModule.EStage.Started);
            if (ret)
            {
                ForeachModule((CoreModule module) =>
                {
                    module.stage = CoreModule.EStage.Updating;
                });
            }
            else
            {
                this.Quit();
            }
        }
        public void Quit()
        {
            if (CoreModule.EStage.Releasing != moduleStage && CoreModule.EStage.Released != moduleStage)
                ExecuteStageFnUtil(moduleStage, CoreModule.EStage.Releasing, CoreModule.EStage.Released);
        }

        public void Update()
        {
            foreach (CoreModule module in m_modules)
            {
                module.Update();
            }
        }

        public void LateUpdate()
        {
            foreach (CoreModule module in m_modules)
            {
                module.LateUpdate();
            }
        }

        public void FixedUpdate()
        {
            foreach (CoreModule module in m_modules)
            {
                module.FixedUpdate();
            }
        }

        public Coroutine StartCoroutine(IEnumerator ie)
        {
            return root.StartCoroutine(ie);
        }
        public void StopCoroutine(Coroutine co)
        {
            root.StopCoroutine(co);
        }
        public void StopAllCoroutines()
        {
            root.StopAllCoroutines();
        }
    }

}
