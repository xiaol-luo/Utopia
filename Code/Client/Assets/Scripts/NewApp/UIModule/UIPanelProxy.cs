
using UnityEngine;

namespace Utopia.UI
{
    public partial class UIPanelProxy : IUIPanelBase
    {
        ResourceLoaderProxy m_resLoader = ResourceLoaderProxy.Create();
        TimerProxy m_timer = NewApp.instance.timerModule.CreateTimerProxy();
        public TimerProxy timer { get { return m_timer; } }
        EventProxy<string> m_eventMgr = NewApp.instance.eventModule.CreateEventProxy();
        public EventProxy<string> eventProxy { get { return m_eventMgr; } }

        UIPanelId m_panelId;
        UIPanelSetting m_panelSetting;
        UIPanelState m_panelState;
        UIPanelState m_wantPanelState;
        UIShowPanelDataBase m_wantShowPanelData;
        bool m_isNewShow = false;
        public bool isNewShow { get { return m_isNewShow; } }
        bool m_isFreezed = true;

        UIPanelMgr m_panelMgr;
        public UIPanelMgr panelMgr { get { return m_panelMgr; } }
        GameObject m_uiRoot;
        GameObject m_root;
        UIPanelBase m_panel;
        GameObject m_panelRoot;

        public GameObject GetRoot()
        {
            return m_root;
        }

        public UIPanelProxy(UIPanelMgr panelMgr, UIPanelId panelId)
        {
            m_panelMgr = panelMgr;
            m_panelId = panelId;
            m_panelSetting = UIPanelDef.GetPanelSetting(m_panelId);
            NewApp.instance.logModule.LogAssert(
                null != m_panelSetting, "panel setting of {0} is null!", m_panelId);
        }

        public bool IsLoading()
        {
            bool ret = (UIPanelState.Loading == m_panelState);
            return ret;
        }
        public bool IsReleased()
        {
            bool ret = false;
            switch (m_panelState)
            {
                case UIPanelState.Released:
                    ret = true;
                    break;
            }
            return ret;
        }
        public bool IsReady()
        {
            if (UIPanelState.Free == m_panelState)
                return false;
            if (this.IsLoading())
                return false;
            if (this.IsReleased())
                return false;
            return true;
        }

        public UIPanelId GetPanelId()
        {
            return m_panelId;
        }

        public UIPanelSetting GetPanelSetting()
        {
            UIPanelSetting ret = UIPanelDef.GetPanelSetting(m_panelId);
            return ret;
        }

        public UIPanelBase GetPanel()
        {
            return m_panel;
        }

        public UIPanelState GetPanelState()
        {
            return m_panelState;
        }

        public void Hide()
        {
            if (this.IsReleased())
                return;
            if (UIPanelState.Hided == m_panelState)
                return;

            NewApp.instance.logModule.LogDebug("UIPanelProxy Hide {0}", m_panelId);

            this.CheckLoadPanel();

            if (this.IsReady())
            {
                m_panel.Hide();
            }
            else // loading
            {
                this.OperaPreHide(null, null);
                this.OperaHided(null, null);
            }
        }

        public void Show(UIShowPanelDataBase panelData)
        {
            if (this.IsReleased())
                return;

            NewApp.instance.logModule.LogDebug("UIPanelProxy Show {0}", m_panelId);

            this.CheckLoadPanel();

            if (this.IsReady())
            {
                m_panel.Show(panelData);
            }
            else // loading
            {
                this.OperaPreShow(null, panelData);
                this.OperaShowed(null, panelData);
            }
        }
        public void Reshow()
        {
            if (this.IsReleased())
                return;
            if (UIPanelState.Showed == m_panelState)
                return;

            NewApp.instance.logModule.LogDebug("UIPanelProxy Reshow {0}", m_panelId);

            this.CheckLoadPanel();

            if (this.IsReady() && m_isNewShow)
            {
                this.Show(m_wantShowPanelData);
            }
            else
            {
                if (this.IsReady())
                {
                    m_panel.Reshow();
                }
                else // loading
                {
                    this.OperaPreReshowed(null, null);
                    this.OperaReshowed(null, null);
                }
            }
        }

        public void Freeze()
        {
            if (this.IsReleased())
                return;
            if (m_isFreezed)
                return;

            NewApp.instance.logModule.LogDebug("UIPanelProxy Freeze {0}", m_panelId);

            if (this.IsReady())
            {
                m_panel.Freeze();
            }
            else
            {
                this.OperaFreezed(null, null);
            }
        }
        public void Unfreeze()
        {
            if (this.IsReleased())
                return;
            if (!m_isFreezed)
                return;

            NewApp.instance.logModule.LogDebug("UIPanelProxy Unfreeze {0}", m_panelId);

            if (this.IsReady())
            {
                m_panel.Unfreeze();
            }
            else
            {
                this.OperaUnfreezed(null, null);
            }
        }

        public void Release()
        {
            if (this.IsReleased())
                return;

            NewApp.instance.logModule.LogDebug("UIPanelProxy Release {0}", m_panelId);

            this.Hide();

            if (this.IsReady())
            {
                m_panel.Release();
            }
            else // loading
            {
                this.OperaPreRelease(null, null);
                this.OperaReleased(null, null);
            }
        }

        public void CheckLoadPanel()
        {
            if (UIPanelState.Free != m_panelState)
                return;

            m_panelState = UIPanelState.Loading;
            m_resLoader.AsyncLoadAsset(m_panelSetting.resPath, this.OnLoadPanelDone);
        }
        protected void OnLoadPanelDone(string resPath, ResourceObserver resOb)
        {
            if (this.IsReleased())
                return;

            NewApp.instance.logModule.LogAssert(resOb.isValid,
                "Load {0} fail, can not load resource {1}", m_panelId, resPath);

            m_panelState = UIPanelState.Loaded;
            GameObject panelGo = resOb.Instantiate<GameObject>();
            panelGo.transform.SetParent(m_panelRoot.transform);
            panelGo.SetActive(true);
            panelGo.transform.localScale = Vector3.one;
            panelGo.transform.localPosition = Vector3.zero;
            m_panel = panelGo.GetComponent<UIPanelBase>();
            m_panel.SetProxy(this);
            m_panel.Init();
            {
                m_panel.SetPanelOperaAction(UIPanelOpera.PreShow, this.OperaPreShow);
                m_panel.SetPanelOperaAction(UIPanelOpera.Showed, this.OperaShowed);
                m_panel.SetPanelOperaAction(UIPanelOpera.PreReshowed, this.OperaPreReshowed);
                m_panel.SetPanelOperaAction(UIPanelOpera.Reshowed, this.OperaReshowed);
                m_panel.SetPanelOperaAction(UIPanelOpera.PreHide, this.OperaPreHide);
                m_panel.SetPanelOperaAction(UIPanelOpera.Hided, this.OperaHided);
                m_panel.SetPanelOperaAction(UIPanelOpera.Freezed, this.OperaFreezed);
                m_panel.SetPanelOperaAction(UIPanelOpera.Unfreezed, this.OperaUnfreezed);
                m_panel.SetPanelOperaAction(UIPanelOpera.PreRelease, this.OperaPreRelease);
                m_panel.SetPanelOperaAction(UIPanelOpera.Released, this.OperaReleased);
            }

            switch (m_wantPanelState)
            {
                case UIPanelState.Showed:
                    {
                        this.Show(m_wantShowPanelData);
                    }
                    break;
                case UIPanelState.Hided:
                    {
                        this.Hide();
                    }
                    break;
            }
        }

        public void Init()
        {
            ResourceObserver resOb = m_panelMgr.GetProxyGoRes(UIPanelMgr.Default_UIPanelProxy_Res_Path);
            m_root = resOb.Instantiate<GameObject>();
            m_root.name = m_panelId.ToString();
            m_uiRoot = m_root.transform.Find("Root").gameObject;
            m_panelRoot = m_root.transform.Find("Root/PanelRoot").gameObject;

            {
                UIPanelProxyBehaviourBase[] behaviours = m_root.GetComponents<UIPanelProxyBehaviourBase>();
                if (null != behaviours &&behaviours.Length > 0)
                {
                    foreach (UIPanelProxyBehaviourBase behaviour in behaviours)
                    {
                        m_behaviours.Add(behaviour);
                        behaviour.Init(this);
                    }
                }
            }
        }

        public bool IsFreezed()
        {
            return m_isFreezed;
        }
    }
}
