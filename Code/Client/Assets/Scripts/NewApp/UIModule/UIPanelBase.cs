
using UnityEngine;

namespace Utopia.UI
{
    public partial class UIPanelBase : MonoBehaviour, IUIPanelBase
    {
        protected UIPanelProxy m_proxy;
        public void SetProxy(UIPanelProxy proxy)
        {
            m_proxy = proxy;
        }

        public void Freeze()
        {
            this.OnFreeze();
        }

        public virtual UIPanelId GetPanelId()
        {
            throw new System.NotImplementedException();
        }

        public UIPanelSetting GetPanelSetting()
        {
            UIPanelSetting ret = UIPanelDef.GetPanelSetting(this.GetPanelId());
            return ret;
        }

        public void Hide()
        {
            if (!this.IsReady())
                return;
            if (UIPanelState.Hided == m_proxy.GetPanelState())
                return;

            m_panelOperas[(int)UIPanelOpera.PreHide](this, null);
            this.OnHide();
            m_panelOperas[(int)UIPanelOpera.Hided](this, null);
        }

        public void Show(UIShowPanelDataBase panelData)
        {
            if (!this.IsReady())
                return;

            m_panelOperas[(int)UIPanelOpera.PreShow](this, panelData);
            this.OnShow(panelData);
            m_panelOperas[(int)UIPanelOpera.Showed](this, panelData);
        }

        public void Unfreeze()
        {
            this.OnUnfreeze();
        }

        protected virtual void OnInit()
        {

        }
        protected virtual void OnShow(UIShowPanelDataBase panelData)
        {
            NewApp.instance.logModule.LogDebug("UIPanelBase OnShow {0}", this.GetPanelId());
        }
        protected virtual void OnHide()
        {
            NewApp.instance.logModule.LogDebug("UIPanelBase OnHide {0}", this.GetPanelId());
        }
        protected virtual void OnFreeze()
        {
            NewApp.instance.logModule.LogDebug("UIPanelBase OnFreeze {0}", this.GetPanelId());
        }
        protected virtual void OnUnfreeze()
        {
            NewApp.instance.logModule.LogDebug("UIPanelBase OnUnfreeze {0}", this.GetPanelId());
        }
        protected virtual void OnReshow()
        {
            NewApp.instance.logModule.LogDebug("UIPanelBase OnReshow {0}", this.GetPanelId());
        }

        public UIPanelState GetPanelState()
        {
            var ret = m_proxy.GetPanelState();
            return ret;
        }

        public void Reshow()
        {
            if (!this.IsReady())
                return;
            if (UIPanelState.Showed == m_proxy.GetPanelState())
                return;

            if (m_proxy.isNewShow)
            {
                m_proxy.Reshow();
            }
            else
            {
                m_panelOperas[(int)UIPanelOpera.PreReshowed](this, null);
                this.OnReshow();
                m_panelOperas[(int)UIPanelOpera.Reshowed](this, null);
            }
        }

        public void Init()
        {
            this.OnInit();
        }

        public void SetPanelProxyFn()
        {

        }

        public bool IsLoading()
        {
            return false;
        }

        public bool IsReleased()
        {
            return m_proxy.IsReleased();
        }

        public bool IsReady()
        {
            return m_proxy.IsReady();
        }
    }
}
