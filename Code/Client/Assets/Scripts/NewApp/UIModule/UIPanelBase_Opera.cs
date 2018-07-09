
using UnityEngine;

namespace Utopia.UI
{
    public partial class UIPanelBase
    {
        System.Action<UIPanelBase, object>[] m_panelOperas = 
            new System.Action<UIPanelBase, object>[(int)UIPanelOpera.Count];
        public void SetPanelOperaAction(UIPanelOpera opera, System.Action<UIPanelBase, object> cb)
        {
            m_panelOperas[(int)opera] = cb;
        }
    }
}
