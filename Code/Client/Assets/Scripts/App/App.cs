using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;
using Utopia.Event;
using Utopia.UI;

namespace Utopia
{
    public class App
    {
        public static App instance { get { return m_instance; } }
        protected static App m_instance = null;
        public static void MakeInstance(MonoBehaviour _owner)
        {
            if (null == m_instance)
            {
                m_instance = new App(_owner);
            }
            else
            {
                Debug.LogError("App is single instance, can only make one instance");
            }
        }
        protected App(MonoBehaviour _mono)
        {
            root = _mono;
            uiRoot = root.transform.Find("RootUI").transform;
        }
        public MonoBehaviour root { get; protected set; }
        public Transform uiRoot { get; protected set; }
        public GameNetwork gameNetwork { get; protected set; }
        public GameConfig gameConfig { get; protected set; }
        public AppStateMgr stateMgr { get; protected set; }
        public Scene scene { get; protected set; }
        public ulong heroId { get; set; }


        bool m_isQuited = false;
        bool m_isStarted = false;
        public UIPanelMgr panelMgr { get; protected set; }
        public NetMgr net { get; protected set; }
        EventProxy<string> m_evProxy;

        public void Awake()
        {
            Core.MakeInstance(this.root);
            m_evProxy = Core.instance.eventMgr.CreateEventProxy();
            panelMgr = new UIPanelMgr(root.transform.Find("RootUI").gameObject);
            net = new NetMgr();

            this.SetupEvents();
            stateMgr = new AppStateMgr();
            gameNetwork = new GameNetwork();
            gameConfig = new GameConfig();
            scene = new Scene();
            gameConfig.Awake();
        }
        public void Start()
        {
            LayerUtil.Init();
            UIPanelDef.InitPanelSettings();
            net.Init();

            bool isAllOk = true;
            do
            {
                if (!gameConfig.Start())
                {
                    Debug.LogError(string.Format("GameConfig Start errno :{0}, error msg :{1}", gameConfig.errno, gameConfig.errMsg));
                    break;
                }
                {
                    Core.instance.Awake();
                    if (CoreModule.EStage.Updating != Core.instance.currStage)
                    {
                        Debug.LogError(string.Format("Core awake fail!"));
                        break;
                    }
                }
                {
                    if (!panelMgr.Init())
                    {
                        {
                            Debug.LogError(string.Format("panelMgr.Init"));
                            break;
                        }
                    }
                }

                isAllOk = true;

            } while (false);

            if (isAllOk)
            {
                m_isStarted = true;
                Core.instance.eventMgr.Fire(AppEvent.GameStarted);
            }
            else
            {
                this.Quit();
            }
        }
        public void FixedUpdate()
        {
            if (m_isQuited || !m_isStarted)
                return;

            if (CoreModule.EStage.Updating == Core.instance.currStage)
            {
                Core.instance.Update();
            }
        }

        public void Quit()
        {
            if (m_isQuited)
                return;

            m_isQuited = true;
            Core.instance.eventMgr.Fire(AppEvent.GameToQuit);
            Core.instance.Release();
        }

        void SetupEvents()
        {
            m_evProxy.Subscribe(AppEvent.UIPanelMgr_LoadPanelProxyResourceFail, OnUIPanelMgrInitFail);
        }
        void OnUIPanelMgrInitFail(string eventName)
        {
            this.Quit();
        }
    }

}