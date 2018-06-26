using NetProto;
using UnityEngine;
using UnityEngine.UI;
using Utopia.Net;

namespace Utopia.UI
{
    public class MainPanel : MonoBehaviour
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

        void OnDestroy()
        {
            m_evProxy.ClearAll();
        }
        void Start()
        {
            ipTxt.text = "127.0.0.1";
            portTxt.text = "10240";

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
