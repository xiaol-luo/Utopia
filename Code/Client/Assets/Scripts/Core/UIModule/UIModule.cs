

using UnityEngine;
using Utopia.UI;

namespace Utopia
{
    public class UIModule : CoreModule
    {
        UIPanelMgr m_panelMgr;
        public UIPanelMgr panelMgr { get { return m_panelMgr; } }
        public UIModule(Core _app) : base(_app, EModule.UIModule)
        {
            
        }

        protected override ERet OnStart()
        {
            ERet ret = base.OnStart();
            UIPanelDef.InitPanelSettings();
            GameObject panelRoot = Core.instance.root.transform.Find("RootUI").gameObject;
            m_panelMgr = new UIPanelMgr(panelRoot);
            m_panelMgr.Init();
            return ret;
        }

        float deltaSec = 0.0f;
        bool isFirst = true;
        protected override void OnFixedUpdate ()
        {
            base.OnFixedUpdate();

            if (isFirst)
            {
                isFirst = false;
                m_panelMgr.ShowPanel(UIPanelId.MainPanel, null);
            }

            return;

            deltaSec += Time.deltaTime;
            if (deltaSec >= 0.3f)
            {
                deltaSec = 0;

                UIPanelId panelId = (UIPanelId)Random.Range(1, (int)UIPanelId.ReserveName_Begin);
                int actionType = Random.Range(0, 10);   
                switch (actionType)
                {
                    case 0:
                    case 4:
                    case 5:
                    case 6:
                        m_panelMgr.ShowPanel(panelId, null);
                        break;
                    case 1:
                        m_panelMgr.HidePanel(panelId);
                        break;
                    case 2:
                        m_panelMgr.ReshowPanel(panelId);
                        break;
                    case 3:
                        m_panelMgr.ReleasePanel(panelId);
                        break;
                    default:
                        {
                            var pp = m_panelMgr.GetCachedPanel(panelId);
                            if (null != pp)
                            {
                                UIPanelBase pb = pp.GetPanel();
                                if (null != pb)
                                {
                                    pb.Hide();
                                    pb.Reshow();
                                    pb.Show(null);
                                    pb.Reshow();
                                }
                            }
                        }
                        break;
                }
            }
        }
    }
}
