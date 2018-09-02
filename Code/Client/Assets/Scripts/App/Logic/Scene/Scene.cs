
using NetProto;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Utopia;
using Utopia.Logic;
using Utopia.UI;
using System;

namespace Utopia
{ 
    public partial class Scene
    {
        bool m_isLoadSceneSucc = false;
        bool m_isLoadingScene = false;
        ulong m_mainHeroId = 0;
        Transform m_rootObstacles = null;
        public Transform rootSceneObejcts { get { return m_rootSceneObjects; } }
        Transform m_rootSceneObjects = null;
        SceneCamera sceneCamera = new SceneCamera();
        ResourceLoaderProxy m_resLoader = ResourceLoaderProxy.Create();
        EventProxy<string> m_evProxy = Core.instance.eventMgr.CreateEventProxy();

        float m_client_startup_sec = 0;
        long m_srv_logic_ms = 0;
        float m_srv_logic_sec = 0;
        public const int MsPerSec = 1000;
        public long nowMs
        {
            get
            {
                float ret = nowSec * MsPerSec;
                return (long)ret;
            }
        }
        public float nowSec
        {
            get
            {
                float ret = Time.realtimeSinceStartup - m_client_startup_sec + m_srv_logic_sec;
                return ret;
            }
        }

        public void EnterScene(string sceneName)
        {
            m_mainHeroId = App.instance.logicMgr.GetModule<SelectHero>().usingHeroObjId;

            m_isLoadSceneSucc = false;
            m_isLoadingScene = true;
            m_resLoader.AsyncLoadScene("Assets/Resources/Levels/Level_Battle.unity", false, OnSceneLoaded);
            {
                // show load scene loading panel
                UILoadingPanelData panelData = new UILoadingPanelData();
                panelData.fnGetContent = () => { return "Loading Scene"; };
                panelData.fnIsDone = () => { return m_isLoadSceneSucc; };
                App.instance.panelMgr.ShowPanel(UIPanelId.LoadingPanel, panelData);
            }
        }
        void OnSceneLoaded(ResourceScene.LoadResult result, string scenePath)
        {
            m_isLoadingScene = false;
            m_isLoadSceneSucc = ResourceScene.LoadResult.Succ == result;
            if (!m_isLoadSceneSucc)
            {
                Core.instance.log.LogError("Scene Load Scene fail {0}", scenePath);
                return;
            }

            LoadNavMesh();

            foreach (GameObject rootGo in SceneManager.GetActiveScene().GetRootGameObjects())
            {
                if (rootGo.name == "SceneObjects")
                {
                    m_rootSceneObjects = rootGo.transform;
                }
                if (rootGo.name == "Obstacles")
                {
                    m_rootObstacles = rootGo.transform;
                }
            }
            {
                GameObject sceneLogicMono = new GameObject();
                sceneLogicMono.name = "SceneLogicMono";
                sceneLogicMono.AddComponent<SceneLogicMono>();
            }
            sceneCamera.InitCamera();
            App.instance.net.gameSrv.Add<RecreateSceneRsp>(PID.RecreateSceneRsp, OnRecreateScene);
            App.instance.net.gameSrv.Add<SceneTimeSync>(PID.SceneTimeSynRsp, OnSyncTime);

            Gizmos_OnSceneLoaded();
            Su_OnSceneLoaded();

            {
                // 通知服务器场景加载完了
                App.instance.net.gameSrv.Send(PID.LoadSceneComplete);
                m_evProxy.Subscribe(SelectHeroModuleDef.Event_OnRspSelectHero, (string evName) => 
                {
                    if (App.instance.logicMgr.GetModule<SelectHero>().usingHeroObjId > 0)
                    {
                        App.instance.net.gameSrv.Send(PID.LoadSceneComplete);
                    }
                });
            }
        }

        public void LeaveScene()
        {
            m_isLoadSceneSucc = false;
            m_isLoadingScene = false;

            App.instance.net.gameSrv.Send(PID.LeaveScene);

            App.instance.net.gameSrv.Remove(PID.SceneTimeSynRsp);
            App.instance.net.gameSrv.Remove(PID.RecreateSceneRsp);

            Gizmos_LeaveScene();
            Su_LeaveScene();

            m_evProxy.ClearAll();
            App.instance.logicMgr.GetModule<SelectHero>().SelectSide(SelectHero.SelectedSide.None);
            sceneCamera.ReleaseCamera();
            m_sceneUnits.Clear();
            rootSceneObejcts.DetachChildren();
        }
        void OnSyncTime(int id, SceneTimeSync msg)
        {
            m_client_startup_sec = Time.realtimeSinceStartup;
            m_srv_logic_ms = msg.Ms;
            m_srv_logic_sec = msg.Sec;
        }

        void OnRecreateScene(int id, RecreateSceneRsp msg)
        {
            if (msg.IsSucc)
            {
                App.instance.stateMgr.ChangeState(EAppState.InLogic);
            }
        }

        public void FixUpdate()
        {
            if (!m_isLoadSceneSucc)
                return;
        }

        public void Update()
        {
            if (!m_isLoadSceneSucc)
                return;

            this.CheckPlayerInput();
            this.UpdateSus();
        }
    }
}