using NetProto;
using UnityEngine;
using UnityEngine.UI;
using Utopia.Net;

namespace Utopia.UI
{
    public class MainPanel : UIPanelBase
    {
        [SerializeField]
        Button netBtn;

        [SerializeField]
        InputField ipTxt;

        [SerializeField]
        InputField portTxt;


        public override UIPanelId GetPanelId()
        {
            return m_proxy.GetPanelId();
        }

        void OnDestroy()
        {
            if (null != m_evProxy)
            {
                m_evProxy.ClearAll();
            }
        }

        bool isGameSrvConnected
        {
            get
            {
                return null != App.instance.net.gameSrv.netAgent.socket &&
                    ClientSocket.State.Connected == App.instance.net.gameSrv.netAgent.socket.state;
            }
        }

        protected override void OnInit()
        {
            base.OnInit();

            ipTxt.text = "127.0.0.1";
            portTxt.text = "10240";

            this.UpdateUI();
            netBtn.onClick.AddListener(() =>
            {
                App.instance.net.gameSrv.Connect(ipTxt.text, int.Parse(portTxt.text));
            });
        }

        void OnRspFreeHero(string evKey, RspFreeHero msg)
        {
            Core.instance.log.LogDebug("OnRspFreeHero {0}", msg.ToString());
        }
        void UpdateUI()
        {
            string netBtnTxt = isGameSrvConnected ? "Disconnect" : "Connect";
            netBtn.transform.Find("Text").GetComponent<Text>().text = netBtnTxt;
        }
    }
}
