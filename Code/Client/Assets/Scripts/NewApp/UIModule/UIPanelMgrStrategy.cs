using System.Collections.Generic;

namespace Utopia.UI
{
    public partial class UIPanelMgr
    {
        public interface IUIPanelMgrStragy
        {
            void OnShowPanel(UIPanelProxy panel);
            void OnHidePanel(UIPanelProxy panel);
            void OnReshowPanel(UIPanelProxy panel);
            void OnReleasePanel(UIPanelProxy panel);
        }

        public class UIPanelIdSet
        {
            public List<UIPanelId>[] panelIds = new List<UIPanelId>[(int)UIPanelShowMode.Count];
        }
        public class UIPanelMgrStragy : IUIPanelMgrStragy
        {   
            protected UIPanelMgr m_panelMgr;
            public UIPanelMgrStragy(UIPanelMgr panelMgr)
            {
                m_panelMgr = panelMgr;
            }

            public void OnHidePanel(UIPanelProxy panel)
            {

            }

            public void OnReleasePanel(UIPanelProxy panel)
            {
            }

            public void OnReshowPanel(UIPanelProxy panel)
            {
            }

            public void OnShowPanel(UIPanelProxy panel)
            {

            }
        }
    }
}