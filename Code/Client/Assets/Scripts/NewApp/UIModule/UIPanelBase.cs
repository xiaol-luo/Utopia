
using UnityEngine;

namespace Utopia.UI
{
    public class UIPanelBase : MonoBehaviour, IUIPanelBase
    {
        UIPanelProxy m_proxy;
        public void SetProxy(UIPanelProxy proxy)
        {
            m_proxy = proxy;
        }

        public void Freeze()
        {
            this.OnFreeze();
        }

        public UIPanelId GetPanelId()
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

        }
        protected virtual void OnHide()
        {

        }
        protected virtual void OnFreeze()
        {

        }
        protected virtual void OnUnfreeze()
        {

        }
        protected virtual void OnReshow()
        {

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
