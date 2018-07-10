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
            base.OnShow();
            m_mask.gameObject.SetActive(true);
        }
        public override void OnReshow()
        {
            base.OnReshow();
            m_mask.gameObject.SetActive(true);
        }
        public override void OnHide()
        {
            base.OnHide();
            m_mask.gameObject.SetActive(false);
        }
    }
}
