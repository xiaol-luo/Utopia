

using UnityEngine;
using Utopia.UI;

namespace Utopia
{
    public class UIModule : AppModule
    {
        UIPanelMgr m_panelMgr;
        public UIPanelMgr panelMgr { get { return m_panelMgr; } }
        public UIModule(NewApp _app) : base(_app, EModule.UIModule)
        {
            
        }

        protected override ERet OnStart()
        {
            ERet ret = base.OnStart();

            GameObject panelRoot = NewApp.instance.root.transform.Find("RootUI").gameObject;
            m_panelMgr = new UIPanelMgr(panelRoot);
            UIPanelDef.InitPanelSettings();
            m_panelMgr.Init();

            return ret;
        }

        bool isFirst = true;
        protected override void OnLateUpdate()
        {
            base.OnLateUpdate();

            if (isFirst)
            {
                isFirst = false;
                m_panelMgr.ShowPanel(UIPanelId.MainPanel, null);
            }
        }
    }
}
