﻿using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;
using Utopia.Event;
using Utopia.Logic;
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
        public GameConfig gameConfig { get; protected set; }
        
        public Scene scene { get; protected set; }
        public ulong heroId { get; set; }


        bool m_isQuited = false;
        public UIPanelMgr panelMgr { get; protected set; }
        public NetMgr net { get; protected set; }
        EventProxy<string> m_evProxy;
        public LogicMgr logicMgr { get; protected set; }
        public AppStateMgr stateMgr { get; protected set; }

        public void Awake()
        {
            Core.MakeInstance(this.root);
            m_evProxy = Core.instance.eventMgr.CreateEventProxy();
            panelMgr = new UIPanelMgr(root.transform.Find("RootUI").gameObject);
            logicMgr = new LogicMgr();
            stateMgr = new AppStateMgr();
            gameConfig = new GameConfig();
            gameConfig.Awake();
            scene = new Scene();
            App.instance.logicMgr.Init();
            net = new NetMgr();
            this.SetupEvents();
        }

        public void Start()
        {
            LayerUtil.Init();
            UIPanelDef.InitPanelSettings();
            stateMgr.ChangeState(EAppState.LiveUpdate, null);

            /*
            net.Init();
            logicMgr.Init();

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
                    logicMgr.Awake();
                }
                {
                    if (!panelMgr.Awake())
                    {
                        {
                            Debug.LogError(string.Format("panelMgr.Awake"));
                            break;
                        }
                    }
                }

                isAllOk = true;

            } while (false);

            if (isAllOk)
            {
                Core.instance.eventMgr.Fire(AppEvent.GameStarted);
            }
            else
            {
                this.Quit();
            }
            */
        }
        public void FixedUpdate()
        {
            if (m_isQuited)
                return;

            stateMgr.UpdateState();

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
            stateMgr.ChangeState(EAppState.Quit, null);
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