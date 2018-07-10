
using System.Collections.Generic;
using UnityEngine;

namespace Utopia.UI
{
    public partial class UIPanelMgr
    {
        protected void OperaShow(UIPanelProxy proxy, object param/*always UIShowPanelDataBase*/)
        {
            UIShowPanelDataBase panelProxy = param as UIShowPanelDataBase;
            m_showStragy.OnShowPanel(proxy);
        }

        protected void OperaReshow(UIPanelProxy proxy, object param/*always null*/)
        {
            m_showStragy.OnReshowPanel(proxy);
        }
        protected void OperaHide(UIPanelProxy proxy, object param/*always null*/)
        {
            m_showStragy.OnHidePanel(proxy);
        }
        protected void OperaRelease(UIPanelProxy proxy, object param/*always null*/)
        {
            UIPanelId panelId = proxy.GetPanelId();
            this.HidePanel(panelId);
            m_cachedPanels.Remove(panelId);
            m_showStragy.OnReleasePanel(proxy);
            GameObject.Destroy(proxy.GetRoot());
        }
    }
}
