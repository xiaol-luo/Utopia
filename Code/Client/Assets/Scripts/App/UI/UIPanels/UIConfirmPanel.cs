using UnityEngine.UI;
using Utopia.Net;

namespace Utopia.UI
{
    public class UIConfirmPanelData : UIShowPanelDataBase
    {
        public string content;
        public System.Action cancelCb;
        public System.Action confirmCb;
    }

    public class UIConfirmPanel : UIPanelBase
    {
        [UnityEngine.SerializeField]
        protected Button confirmBtn;
        [UnityEngine.SerializeField]
        protected Button cancelBtn;
        [UnityEngine.SerializeField]
        protected Text contentTxt;

        protected override void OnInit()
        {
            base.OnInit();
            confirmBtn.onClick.AddListener(() =>
            {
                if (null != m_panelData && null != m_panelData.confirmCb)
                {
                    m_panelData.confirmCb();
                }
                this.Hide();
            });

            cancelBtn.onClick.AddListener( () =>
            {
                if (null != m_panelData && null != m_panelData.cancelCb)
                {
                    m_panelData.cancelCb();
                }
                this.Hide();
            });
        }

        UIConfirmPanelData m_panelData;
        protected override void OnShow(UIShowPanelDataBase panelData)
        {
            base.OnShow(panelData);
            m_panelData = panelData as UIConfirmPanelData;
            if (null == m_panelData)
            {
                Core.instance.timer.Add(() => { this.Hide(); }, 0);
                return;
            }
            contentTxt.text = m_panelData.content;
        }
    }
}