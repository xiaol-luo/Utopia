using UnityEngine;
using UnityEngine.UI;

namespace Utopia.UI
{
    public class UIPanelProxyBehaviourFullScreenHide : UIPanelProxyBehaviourBase
    {
        protected Transform m_uiRoot;
        public override void Init(UIPanelProxy proxy)
        {
            base.Init(proxy);
            Transform root = m_proxy.GetRoot().transform;
            m_uiRoot = root.Find("Root");

            m_proxy.eventProxy.Subscribe(UIPanelEventDef.OneFullPanelShow, this.OnOneFullPanelShow);
            m_proxy.eventProxy.Subscribe(UIPanelEventDef.AllFullPanelHide, this.OnAllFullPanelHide);

            this.CheckHide();
        }

        void OnOneFullPanelShow(string evName)
        {
            this.CheckHide();
        }
        void OnAllFullPanelHide(string evName)
        {
            this.CheckHide();
        }

        bool isHide = false;
        void CheckHide()
        {
            UIPanelSetting selfPs = m_proxy.GetPanelSetting();
            if (null == selfPs || selfPs.showMode >= UIPanelShowMode.HideOther)
                return;

            UIPanelId topestActivePanelId = m_proxy.panelMgr.GetTopestActivePanelId();
            UIPanelSetting topestActivePs = UIPanelDef.GetPanelSetting(topestActivePanelId);
            UIPanelShowMode topestActiveShowMode = UIPanelShowMode.Coexist;
            if (null != topestActivePs)
                topestActiveShowMode = topestActivePs.showMode;

            if (isHide)
            {
                if (topestActiveShowMode < UIPanelShowMode.HideOther)
                {
                    isHide = false;
                    m_uiRoot.localScale = Vector3.one;
                }
            }
            else
            {
                if (topestActiveShowMode >= UIPanelShowMode.HideOther)
                {
                    isHide = true;
                    m_uiRoot.localScale = Vector3.zero;
                }
            }
        }
    }
}
