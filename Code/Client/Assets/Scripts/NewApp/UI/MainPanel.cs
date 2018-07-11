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
            portTxt.text = "10250";

            m_evProxy = NewApp.instance.eventModule.CreateEventProxy();
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetConnected, OnGameSrvConnected);
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetClosed, OnGameSrvClosed);
            m_evProxy.Subscribe<RspFreeHero>(GameSrvNetProxy.ProtoEventName(ProtoId.PidRspFreeHero), OnRspFreeHero);

            this.UpdateUI();
            netBtn.onClick.AddListener(() =>
            {
                bool isGameSrvConnected = false;
                if (null != NewApp.instance.netModule.gameSrv.netAgent.socket &&
                    ClientSocket.State.Connected == NewApp.instance.netModule.gameSrv.netAgent.socket.state)
                {
                    isGameSrvConnected = true;
                }
                if (!isGameSrvConnected)
                    NewApp.instance.netModule.gameSrv.Connect(ipTxt.text, int.Parse(portTxt.text));
                else
                    NewApp.instance.netModule.gameSrv.Close();
            });

            logicBtn.onClick.AddListener(() =>
            {
                NewApp.instance.netModule.gameSrv.Send(ProtoId.PidQueryFreeHero);

                SelectHeroReq req = new SelectHeroReq() { HeroId = 1 };
                // for test
                NewApp.instance.netModule.gameSrv.Send((int)ProtoId.PidSelectHeroReq, req);
            });
        }

        void OnGameSrvConnected(string evName, CommonNetProxy evParam)
        {
            this.UpdateUI();
        }

        void OnGameSrvClosed(string evName, CommonNetProxy evParam)
        {
            this.UpdateUI();
            UIConfirmPanelData cpd = new UIConfirmPanelData();
            cpd.content = "cancel is to hide panel, ok to show loading panel";
            cpd.confirmCb = () =>
            {
                UILoadingPanelData lpd = new UILoadingPanelData();
                int tickTimes = 10;
                lpd.fnIsDone = () =>
                {
                    return tickTimes <= 0;
                };
                string txt = "10";
                lpd.fnGetContent = () =>
                {
                    return txt;
                };
                NewApp.instance.panelMgr.ShowPanel(UIPanelId.LoadingPanel, lpd);
                m_proxy.timer.Add(() =>
                {
                    --tickTimes;
                    txt = tickTimes.ToString();
                }, 0, tickTimes, 1.0f);
            };
            NewApp.instance.panelMgr.ShowPanel(UIPanelId.ConfirmPanel, cpd);
        }

        void OnRspFreeHero(string evKey, RspFreeHero msg)
        {
            NewApp.instance.logModule.LogDebug("OnRspFreeHero {0}", msg.ToString());
        }
        void UpdateUI()
        {
            bool isGameSrvConnected = false;
            if (null != NewApp.instance.netModule.gameSrv.netAgent.socket &&
                ClientSocket.State.Connected == NewApp.instance.netModule.gameSrv.netAgent.socket.state)
            {
                isGameSrvConnected = true;
            }
            string netBtnTxt = isGameSrvConnected ? "Disconnect" : "Connect";
            netBtn.transform.Find("Text").GetComponent<Text>().text = netBtnTxt;

            logicBtn.gameObject.SetActive(isGameSrvConnected);
        }
    }
}
