using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;


namespace Utopia
{
    public class NewApp
    {
        public static NewApp instance { get { return m_instance; } }
        protected static NewApp m_instance = null;
        public static void MakeInstance(MonoBehaviour _owner)
        {
            if (null == m_instance)
                m_instance = new NewApp(_owner);
            else
                Debug.LogError("NewApp is single instance, can only make one instance");
        }

        public LogModule logModule
        {
            get
            {
                return m_modules[AppModule.EModule.LogModule] as LogModule;
            }
        }

        public DateTimeModule datetimeModule
        {
            get
            {
                return m_modules[AppModule.EModule.DateTimeModule] as DateTimeModule;
            }
        }

        public MonoBehaviour root { get; protected set; }

        public AppModule.EStage moduleStage { get; protected set; }

        const int EModuleCount = (int)AppModule.EModule.Count;
        AppModule[] m_modules = new AppModule[EModuleCount];

        public void ForeachModule(System.Action<AppModule> _fn)
        {
            System.Action<AppModule, object, object> fn = (AppModule module, object p1, object p2) => { _fn(module); };
            foreach (AppModule module in m_modules)
            {
                fn(module, null, null);
            }
        }
        public void ForeachModule(System.Action<AppModule, object, object> fn, object inParam, ref object outParam)
        {
            foreach (AppModule module in m_modules)
            {
                fn(module, inParam, outParam);
            }
        }
        bool ExecuteStageFnUtil(AppModule.EStage preStage, AppModule.EStage fromStage, AppModule.EStage toStage)
        {
            this.moduleStage = fromStage;

            bool allModuleStageMatch = true;
            ForeachModule((AppModule module) =>
            {
                if (AppModule.EStage.Releasing !=  fromStage)
                    allModuleStageMatch &= (module.stage == preStage);
            });
            if (!allModuleStageMatch)
                return false;

            ForeachModule((AppModule module) =>
            {
                module.stage = fromStage;
            });

            int failModuleId = AppModule.EModule.Count;
            while (true)
            {
                bool allReady = true;
                foreach (AppModule module in m_modules)
                {
                    if (toStage == module.stage)
                        continue;

                    AppModule.ERet ret = AppModule.ERet.Fail;
                    switch(fromStage)
                    {
                        case AppModule.EStage.Awaking:
                            {
                                ret = module.Awake();
                            }
                            break;
                        case AppModule.EStage.Staring:
                            {
                                ret = module.Start();
                            }
                            break;
                        case AppModule.EStage.Releasing:
                            {
                                ret = module.Release();
                            }
                            break;
                    }
                    if (AppModule.ERet.Fail == ret)
                    {
                        failModuleId = module.moduleId;
                        break;
                    }
                    if (toStage != module.stage)
                        allReady = false;
                }
                if (failModuleId != AppModule.EModule.Count)
                {
                    Debug.LogFormat("AppModule {0} try from {1} to {2} ", fromStage, toStage, failModuleId);
                    break;
                }
                if (allReady)
                    break;
            }
            bool returnVal= AppModule.EModule.Count == failModuleId;
            if (returnVal)
                this.moduleStage = toStage;
            return returnVal;
        }
        protected NewApp(MonoBehaviour _root)
        {
            root = _root;

            LayerUtil.Init();

            m_modules[AppModule.EModule.UIModule] = new UIModule(this);
            m_modules[AppModule.EModule.CameraModule] = new CameraModule(this);
            m_modules[AppModule.EModule.DateTimeModule] = new DateTimeModule(this);
            m_modules[AppModule.EModule.TimerModule] = new TimerModule(this);
            m_modules[AppModule.EModule.LogModule] = new LogModule(this);
            m_modules[AppModule.EModule.EventModule] = new EventModule(this);
            m_modules[AppModule.EModule.NetModule] = new NetModule(this);
            m_modules[AppModule.EModule.ResourceModule] = new ResourceModule(this);

            moduleStage = AppModule.EStage.Free;
            ForeachModule((AppModule module) => {
                module.Init();
            });
            moduleStage = AppModule.EStage.Inited;
        }



        public void Awake()
        {
            bool ret = ExecuteStageFnUtil(AppModule.EStage.Inited, AppModule.EStage.Awaking, AppModule.EStage.Awaked);
            if (!ret)
                this.Quit();
        }
        public void Start()
        {
            bool ret = ExecuteStageFnUtil(AppModule.EStage.Awaked, AppModule.EStage.Staring, AppModule.EStage.Started);
            if (ret)
            {
                ForeachModule((AppModule module) =>
                {
                    module.stage = AppModule.EStage.Updating;
                });
            }
            else
            {
                this.Quit();
            }
        }
        public void Quit()
        {
            if (AppModule.EStage.Releasing != moduleStage && AppModule.EStage.Released != moduleStage)
                ExecuteStageFnUtil(moduleStage, AppModule.EStage.Releasing, AppModule.EStage.Released);
        }

        public void Update()
        {
            foreach (AppModule module in m_modules)
            {
                module.Update();
            }
        }

        public void LateUpdate()
        {
            foreach (AppModule module in m_modules)
            {
                module.LateUpdate();
            }
        }

        public void FixedUpdate()
        {
            foreach (AppModule module in m_modules)
            {
                module.FixedUpdate();
            }
        }
    }

}
