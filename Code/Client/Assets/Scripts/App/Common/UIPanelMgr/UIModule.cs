

using UnityEngine;
using Utopia.UI;

namespace Utopia
{
    public class UIModule
    {
        UIPanelMgr m_panelMgr;
        public UIPanelMgr panelMgr { get { return m_panelMgr; } }

        protected void OnStart()
        {
            UIPanelDef.InitPanelSettings();
            GameObject panelRoot = Core.instance.root.transform.Find("RootUI").gameObject;
            m_panelMgr = new UIPanelMgr(panelRoot);
            m_panelMgr.Init();
        }
    }
}
