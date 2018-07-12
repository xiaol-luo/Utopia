using UnityEngine;

namespace Utopia.UI
{
    public abstract class UIPanelProxyBehaviourBase : MonoBehaviour
    {
        protected UIPanelProxy m_proxy;
        public virtual void Init(UIPanelProxy proxy)
        {
            m_proxy = proxy;
        }

        public virtual void OnShow()
        {

        }
        public virtual void OnReshow()
        {

        }
        public virtual void OnHide()
        {

        }
        public virtual void OnRelease()
        {

        }
        public virtual void OnFreeze()
        {

        }
        public virtual void OnUnfreeze()
        {

        }
    }
}
