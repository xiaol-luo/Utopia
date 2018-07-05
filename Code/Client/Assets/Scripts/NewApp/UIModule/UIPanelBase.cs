
using UnityEngine;

namespace Utopia.UI
{
    public class UIPanelBase : MonoBehaviour, IUIPanelBase
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
            this.OnHide();
        }

        public void Show(UIShowPanelDataBase panelData)
        {
            this.OnShow();
        }

        public void Unfreeze()
        {
            this.OnUnfreeze();
        }

        protected virtual void OnInit()
        {

        }
        protected virtual void OnShow()
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
            this.OnReshow();
        }

        public void Init()
        {
            this.OnInit();
        }
    }
}
