using UnityEngine;
using UnityEngine.UI;

namespace Utopia.UI
{
    public class UIPanelProxyBehaviourMask : UIPanelProxyBehaviourBase
    {
        protected Image m_mask;
        public override void Init(UIPanelProxy proxy)
        {
            base.Init(proxy);
            Transform root = m_proxy.GetRoot().transform;
            m_mask = root.Find("Root/Mask").GetComponent<Image>();
        }

        public override void OnShow()
        {
            if (UIPanelShowMode.Coexist == m_proxy.GetPanelSetting().showMode)
                return;

            base.OnShow();
            m_mask.gameObject.SetActive(true);
        }
        public override void OnReshow()
        {
            if (UIPanelShowMode.Coexist == m_proxy.GetPanelSetting().showMode)
                return;

            base.OnReshow();
            m_mask.gameObject.SetActive(true);
        }
        public override void OnHide()
        {
            if (UIPanelShowMode.Coexist == m_proxy.GetPanelSetting().showMode)
                return;

            base.OnHide();
            m_mask.gameObject.SetActive(false);
        }
    }
}
