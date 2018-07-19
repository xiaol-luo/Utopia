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

            m_proxy.evProxy.Subscribe<UIPanelEventDef.PanelIdChange>(UIPanelEventDef.FullScreenPanelOnTop, this.OnOneFullPanelShow);
            m_proxy.evProxy.Subscribe<UIPanelEventDef.PanelIdChange>(UIPanelEventDef.FullScreenPanelNotOnTop, this.OnAllFullPanelHide);

            this.CheckHide();
        }

        void OnOneFullPanelShow(string evName, UIPanelEventDef.PanelIdChange pic)
        {
            this.CheckHide();
        }
        void OnAllFullPanelHide(string evName, UIPanelEventDef.PanelIdChange pic)
        {
            this.CheckHide();
        }

        bool isHide = false;
        void CheckHide()
        {
            UIPanelSetting selfPs = m_proxy.GetPanelSetting();
            if (null == selfPs || 
                UIPanelDef.InFullScreenLayers(selfPs.panelLayer) || 
                UIPanelLayer.Loading == selfPs.panelLayer)
                return;

            UIPanelId topestActivePanelId = m_proxy.panelMgr.GetTopestActivePanelId();
            UIPanelSetting topestActivePs = UIPanelDef.GetPanelSetting(topestActivePanelId);
            UIPanelLayer topestActivePanelLayer = UIPanelLayer.Coexist_0;
            if (null != topestActivePs)
                topestActivePanelLayer = topestActivePs.panelLayer;
            if (UIPanelLayer.Loading == topestActivePanelLayer)
                return;

            if (isHide)
            {
                if (!UIPanelDef.InFullScreenLayers(topestActivePanelLayer))
                {
                    isHide = false;
                    m_uiRoot.localScale = Vector3.one;
                }
            }
            else
            {
                if (UIPanelDef.InFullScreenLayers(topestActivePanelLayer))
                {
                    isHide = true;
                    m_uiRoot.localScale = Vector3.zero;
                }
            }
        }
    }
}
