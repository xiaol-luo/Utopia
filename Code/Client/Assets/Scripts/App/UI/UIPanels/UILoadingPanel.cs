using UnityEngine.UI;
using Utopia.Net;
using UnityEngine;

namespace Utopia.UI
{
    public class UILoadingPanelData : UIShowPanelDataBase
    {
        public delegate string FnGetContent();
        public delegate bool FnIsDone();
        public FnGetContent fnGetContent;
        public FnIsDone fnIsDone;
    }

    public class UILoadingPanel : UIPanelBase
    {
        [SerializeField]
        Text contentTxt;

        TimerProxy m_timerProxy;
        UILoadingPanelData m_panelData;

        protected override void OnInit()
        {
            base.OnInit();
            m_timerProxy = Core.instance.timer.CreateTimerProxy();
        }

        protected override void OnShow(UIShowPanelDataBase panelData)
        {
            base.OnShow(panelData);
            m_panelData = panelData as UILoadingPanelData;
            if (null == m_panelData || null == m_panelData.fnIsDone)
            {
                m_timerProxy.Add(() => { this.Hide(); }, 0);
                return;
            }

            m_timerProxy.Add(this.UpdateLogic, 0, -1, 0.5f);
        }

        protected override void OnHide()
        {
            base.OnHide();
            m_timerProxy.ClearAll();
        }

        void UpdateLogic()
        {
            if (null == m_panelData || null == m_panelData.fnIsDone)
            {
                this.Hide();
                return;
            }

            contentTxt.gameObject.SetActive(false);
            if (null != m_panelData.fnGetContent)
            {
                contentTxt.gameObject.SetActive(true);
                contentTxt.text = m_panelData.fnGetContent();
            }

            if (m_panelData.fnIsDone())
            {
                this.Hide();
            }
        }
    }
}