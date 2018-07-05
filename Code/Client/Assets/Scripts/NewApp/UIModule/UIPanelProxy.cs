
using UnityEngine;

namespace Utopia.UI
{
    public class UIPanelProxy : IUIPanelBase
    {
        ResourceLoaderProxy m_resLoader = ResourceLoaderProxy.Create();
        TimerProxy m_timer = NewApp.instance.timerModule.CreateTimerProxy();
        EventProxy<string> m_eventMgr = NewApp.instance.eventModule.CreateEventProxy();


        UIPanelId m_panelId;
        UIPanelSetting m_panelSetting;
        UIPanelState m_panelState;
        UIPanelState m_wantPanelState;
        UIShowPanelDataBase m_wantShowPanelData;
        bool m_isNewShow = false;
        bool m_isFreezed = true;

        UIPanelMgr m_panelMgr;
        GameObject m_root;
        UIPanelBase m_panel;
        GameObject m_mask;
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

        public UIPanelState GetPanelState()
        {
            return m_panelState;
        }

        // maybe just for debug
        enum OperaType
        {
            Show,
            Hide,
            Freeze,
            Unfreeze,
            Count
        }
        bool []m_isOpering = new bool [(int)OperaType.Count]; // ∑¿÷π≤Ÿ◊˜÷ÿ»Î
        bool LockOpera(OperaType op)
        {
            bool ret = false;
            if (!m_isOpering[(int)op])
            {
                ret = true;
                m_isOpering[(int)op] = true;
            }
            return ret;
        }
        void UnlockOpera(OperaType op)
        {
            m_isOpering[(int)op] = false;
        }

        public void Hide()
        {
            if (this.IsReleased())
                return;
            if (UIPanelState.Hided == m_panelState)
                return;

            OperaType op = OperaType.Hide;
            if (!this.LockOpera(op))
                return;

            this.CheckLoadPanel();
            this.Freeze();
            {
                // TOOD: process proxy self logic
            }
            if (this.IsReady())
            {
                m_panelState = UIPanelState.Hided;
                m_panel.Hide();
            }
            else // loading
            {
                m_wantPanelState = UIPanelState.Hided;
            }

            m_root.SetActive(false);
            this.UnlockOpera(op);
        }

        public void Show(UIShowPanelDataBase panelData)
        {
            if (this.IsReleased())
                return;

            OperaType op = OperaType.Show;
            if (!this.LockOpera(op))
                return;

            m_isNewShow = true;
            m_wantShowPanelData = null;

            this.CheckLoadPanel();
            m_root.SetActive(true);
            this.Unfreeze();
            {
                // TOOD: process proxy self logic
            }
            if (this.IsReady())
            {
                m_panelState = UIPanelState.Showed;
                m_panel.Show(panelData);
                m_isNewShow = false;
            }
            else // loading
            {
                m_wantPanelState = UIPanelState.Showed;
                m_wantShowPanelData = panelData;
            }

            this.UnlockOpera(op);
        }
        public void Reshow()
        {
            if (this.IsReleased())
                return;
            if (UIPanelState.Showed == m_panelState)
                return;
            OperaType op = OperaType.Show;
            if (!this.LockOpera(op))
                return;

            this.CheckLoadPanel();
            m_root.SetActive(true);
            if (this.IsReady() && m_isNewShow)
            {
                this.Show(m_wantShowPanelData);
            }
            else
            {
                m_root.SetActive(true);
                this.Unfreeze();
                {
                    // TOOD: process proxy self logic
                }
                if (this.IsReady())
                {
                    m_panelState = UIPanelState.Showed;
                    m_panel.Reshow();
                }
                else // loading
                {
                    m_wantPanelState = UIPanelState.Showed;
                }
            }
            this.UnlockOpera(op);
        }

        public void Freeze()
        {
            if (this.IsReleased())
                return;
            if (m_isFreezed)
                return;
            if (!this.LockOpera(OperaType.Freeze))
                return;

            m_isFreezed = true;
            {
                // TOOD: process proxy self logic
            }
            if (this.IsReady())
            {
                m_panel.Freeze();
            }
            this.UnlockOpera(OperaType.Freeze);
        }
        public void Unfreeze()
        {
            if (this.IsReleased())
                return;
            if (!m_isFreezed)
                return;
            if (!this.LockOpera(OperaType.Unfreeze))
                return;

            m_isFreezed = false;
            {
                // TOOD: process proxy self logic
            }
            if (this.IsReady())
            {
                m_panel.Unfreeze();
            }
            this.UnlockOpera(OperaType.Unfreeze);
        }

        public virtual void Release()
        {
            if (this.IsReleased())
                return;

            this.Hide();
            m_panelState = UIPanelState.Released;
            m_root.transform.SetParent(null);
            m_resLoader.Release();
            m_timer.ClearAll();
            m_eventMgr.ClearAll();
        }

        protected void CheckLoadPanel()
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
            m_panel = panelGo.GetComponent<UIPanelBase>();
            panelGo.transform.SetParent(m_panelRoot.transform);
            m_panel.Init();

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
            m_root.SetActive(true);
            m_root.transform.localPosition = Vector3.zero;
            m_root.transform.localScale = Vector3.one;
            m_panelRoot = m_root.transform.Find("PanelRoot").gameObject;
            m_mask = m_root.transform.Find("Mask").gameObject;
        }
    }
}
