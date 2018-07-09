
using UnityEngine;

namespace Utopia.UI
{
    public partial class UIPanelProxy
    {
        System.Action<UIPanelProxy, object>[] m_panelOperas = 
            new System.Action<UIPanelProxy, object>[(int)UIPanelOpera.Count];
        public void SetPanelOperaAction(UIPanelOpera opera, System.Action<UIPanelProxy, object> cb)
        {
            m_panelOperas[(int)opera] = cb;
        }

        protected void OperaPreShow(UIPanelBase panel, object param/*always UIShowPanelDataBase*/)
        {
            m_uiRoot.SetActive(true);
            this.Unfreeze();

            if (null != panel)
            {
                m_isNewShow = false;
                m_wantShowPanelData = null;
            }
            else
            {
                m_isNewShow = true;
                m_wantShowPanelData = param as UIShowPanelDataBase;
            }
        }

        protected void OperaShowed(UIPanelBase panel, object param/*always UIShowPanelDataBase*/)
        {
            if (null != panel)
            {
                m_panelState = UIPanelState.Showed;
            }
            else
            {
                m_wantPanelState = UIPanelState.Showed;
            }
            m_panelOperas[(int)UIPanelOpera.Showed](this, param);
        }

        protected void OperaPreReshowed(UIPanelBase panel, object param/*always null*/)
        {
            if (null != panel && m_isNewShow)
            {
                this.Show(m_wantShowPanelData);
            }
            else
            {
                m_uiRoot.SetActive(true);
                this.Unfreeze();
            }
        }
        protected void OperaReshowed(UIPanelBase panel, object param/*always null*/)
        {
            if (null != panel)
            {
                m_panelState = UIPanelState.Showed;
            }
            else
            {
                m_wantPanelState = UIPanelState.Showed;
            }
            m_panelOperas[(int)UIPanelOpera.Reshowed](this, param);
        }
        protected void OperaPreHide(UIPanelBase panel, object param/*always null*/)
        {
            this.Freeze();
        }
        protected void OperaHided(UIPanelBase panel, object param/*always null*/)
        {
            if (null != panel)
            {
                m_panelState = UIPanelState.Hided;
            }
            else
            {
                m_wantPanelState = UIPanelState.Hided;
            }
            
            m_uiRoot.SetActive(false);
            m_panelOperas[(int)UIPanelOpera.Hided](this, param);
        }
    }
}
