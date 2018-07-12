
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
            if (this.IsFreezed())
                return;

            this.OnFreeze();
            m_panelOperas[(int)UIPanelOpera.Freezed](this, null);
        }

        public virtual UIPanelId GetPanelId()
        {
            return m_proxy.GetPanelId();
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
            if (!this.IsFreezed())
                return;

            this.OnUnfreeze();
            m_panelOperas[(int)UIPanelOpera.Unfreezed](this, null);
        }

        protected virtual void OnInit()
        {

        }
        protected virtual void OnShow(UIShowPanelDataBase panelData)
        {
            Core.instance.logModule.LogDebug("UIPanelBase OnShow {0}", this.GetPanelId());
        }
        protected virtual void OnHide()
        {
            Core.instance.logModule.LogDebug("UIPanelBase OnHide {0}", this.GetPanelId());
        }
        protected virtual void OnFreeze()
        {
            Core.instance.logModule.LogDebug("UIPanelBase OnFreeze {0}", this.GetPanelId());
        }
        protected virtual void OnUnfreeze()
        {
            Core.instance.logModule.LogDebug("UIPanelBase OnUnfreeze {0}", this.GetPanelId());
        }
        protected virtual void OnReshow()
        {
            Core.instance.logModule.LogDebug("UIPanelBase OnReshow {0}", this.GetPanelId());
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

        public bool IsFreezed()
        {
            return m_proxy.IsFreezed();
        }

        public void Release()
        {
            if (this.IsReleased())
                return;
        }

        protected virtual void OnRelease()
        {
            if (!this.IsReady())
                return;

            m_panelOperas[(int)UIPanelOpera.PreRelease](this, null);
            this.OnRelease();
            m_panelOperas[(int)UIPanelOpera.Released](this, null);
        }
    }
}
