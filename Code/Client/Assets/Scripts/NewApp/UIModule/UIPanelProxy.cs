
using UnityEngine;

namespace Utopia.UI
{
    public class UIPanelProxy : IUIPanelBase
    {
        UIPanelId m_panelId;
        UIPanelSetting m_panelSetting;
        UIPanelState m_panelState;
        UIPanelState m_wantPanelState;
        UIShowPanelDataBase m_wantShowPanelData;
        bool m_isNewShow = false;

        UIPanelMgr m_panelMgr;
        GameObject m_root;
        UIPanelBase m_panel;
        GameObject m_mask;
        GameObject m_panelRoot;

        GameObject GetRoot()
        {
            return m_root;
        }

        public UIPanelProxy(UIPanelMgr panelMgr, UIPanelId panelId, ResourceObserver goRes)
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
                case UIPanelState.Releasing:
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

        public void Freeze()
        {
            if (UIPanelState.Showed != m_panelState)
                return;
            if (!this.LockOpera(OperaType.Freeze))
                return;

            m_panelState = UIPanelState.Freezed;
            m_panel.Freeze();

            this.UnlockOpera(OperaType.Freeze);
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

            OperaType op = OperaType.Hide;
            if (!this.LockOpera(op))
                return;

            m_isNewShow = false;
            m_wantShowPanelData = null;

            this.CheckLoadPanel();

            if (this.IsReady())
            {
                if (UIPanelState.Loaded == m_panelState)
                {
                    // do nothing
                }
                if (UIPanelState.Showed == m_panelState)
                {
                    this.Freeze();
                }
                if (UIPanelState.Freezed == m_panelState)
                {
                    // do nothing
                }

                bool doHideLogic = (UIPanelState.Hided != m_panelState);
                m_panelState = UIPanelState.Hided;
                if (doHideLogic)
                {
                    m_panel.Hide();
                }
            }
            else // loading
            {
                m_wantPanelState = UIPanelState.Hided;
            }

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
            this.CheckLoadPanel();

            if (this.IsReady())
            {
                if (UIPanelState.Loaded == m_panelState || UIPanelState.Showed == m_panelState)
                {
                    // do nothing
                }
                if (UIPanelState.Hided == m_panelState || UIPanelState.Freezed == m_panelState)
                {
                    this.Unfreeze();
                }

                m_panelState = UIPanelState.Showed;
                m_panel.Show(panelData);
            }
            else // loading
            {
                m_wantPanelState = UIPanelState.Showed;
                m_wantShowPanelData = panelData;
            }

            this.UnlockOpera(op);
        }

        public void Unfreeze()
        {
            if (!this.LockOpera(OperaType.Unfreeze))
                return;

            if (this.IsReady())
            {
                
            }
            else // loading
            {
                // m_wantShowPanelData = 
            }

            this.UnlockOpera(OperaType.Unfreeze);
        }

        public virtual void Release()
        {

        }

        protected void CheckLoadPanel()
        {
            if (UIPanelState.Free != m_panelState)
                return;

            m_panelState = UIPanelState.Loading;
            // todo
        }

        public void Reshow()
        {

        }

        public void Init()
        {
            ResourceObserver resOb = m_panelMgr.GetProxyGoRes(UIPanelMgr.Default_UIPanelProxy_Res_Path);
            m_root = resOb.Instantiate<GameObject>();
            m_panelRoot = m_root.transform.Find("PanelRoot").gameObject;
            m_mask = m_root.transform.Find("Mask").gameObject;
        }
    }
}
