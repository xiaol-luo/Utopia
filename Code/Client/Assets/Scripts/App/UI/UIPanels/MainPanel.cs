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
        Button logicBtn;

        [SerializeField]
        InputField ipTxt;

        [SerializeField]
        InputField portTxt;

        EventProxy<string> m_evProxy;

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

        protected override void OnInit()
        {
            base.OnInit();

            ipTxt.text = "127.0.0.1";
            portTxt.text = "10240";

            m_evProxy = Core.instance.eventMgr.CreateEventProxy();
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetConnected, OnGameSrvConnected);
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetClosed, OnGameSrvClosed);
            m_evProxy.Subscribe<RspFreeHero>(GameSrvNetProxy.ProtoEventName(ProtoId.PidRspFreeHero), OnRspFreeHero);

            this.UpdateUI();
            netBtn.onClick.AddListener(() =>
            {
                bool isGameSrvConnected = false;
                if (null != App.instance.net.gameSrv.netAgent.socket &&
                    ClientSocket.State.Connected == App.instance.net.gameSrv.netAgent.socket.state)
                {
                    isGameSrvConnected = true;
                }
                if (!isGameSrvConnected)
                    App.instance.net.gameSrv.Connect(ipTxt.text, int.Parse(portTxt.text));
                else
                    App.instance.net.gameSrv.Close();
            });

            logicBtn.onClick.AddListener(() =>
            {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.QueryFreeHero();
                App.instance.panelMgr.ShowPanel(UIPanelId.SelectHeroPanel);
                this.Hide();
            });
        }

        void OnGameSrvConnected(string evName, CommonNetProxy evParam)
        {
            this.UpdateUI();
        }

        void OnGameSrvClosed(string evName, CommonNetProxy evParam)
        {
            this.UpdateUI();
        }

        void OnRspFreeHero(string evKey, RspFreeHero msg)
        {
            Core.instance.log.LogDebug("OnRspFreeHero {0}", msg.ToString());
        }
        void UpdateUI()
        {
            bool isGameSrvConnected = false;
            CommonNetProxy xx = App.instance.net.gameSrv;
            if (null != App.instance.net.gameSrv.netAgent.socket &&
                ClientSocket.State.Connected == App.instance.net.gameSrv.netAgent.socket.state)
            {
                isGameSrvConnected = true;
            }
            string netBtnTxt = isGameSrvConnected ? "Disconnect" : "Connect";
            netBtn.transform.Find("Text").GetComponent<Text>().text = netBtnTxt;

            logicBtn.gameObject.SetActive(isGameSrvConnected);
        }
    }
}
