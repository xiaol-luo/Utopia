using UnityEngine;
using UnityEditor;
using Utopia.Net;
using Utopia.UI;
using Utopia;
using System.Collections.Generic;

namespace Utopia.Logic
{
    public class GameNet : LogicBase
    {
        public override ELogicName GetModuleName()
        {
            return ELogicName.GameNet;
        }
        
        protected override void OnAwake()
        {
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetConnected, OnGameSrvConnected);
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetClosed, OnGameSrvClosed);

            /*
            m_evProxy.Subscribe<NetProto.RspFreeHero>(
                GameSrvNetProxy.ProtoEventName(NetProto.PID.RspFreeHero), OnRspFreeHero);
            m_evProxy.Subscribe<NetProto.SelectHeroRsp>(
                GameSrvNetProxy.ProtoEventName(NetProto.PID.SelectHeroRsp), OnRspSelectHero);
                */
        }

        protected override void OnInit()
        {
            
        }

        protected override void OnRelease()
        {

        }

        string m_cached_ip = string.Empty;
        int m_cached_port = 0;
        public void Connect(string ip, int port)
        {
            this.Disconnect();
            m_cached_ip = ip;
            m_cached_port = port;
            App.instance.net.gameSrv.Connect(ip, port);
        }

        public void Reconnect()
        {
            this.Disconnect();
            Connect(m_cached_ip, m_cached_port);
        }

        public void Disconnect()
        {
            App.instance.net.gameSrv.Close();
        }

        void OnGameSrvConnected(string evName, CommonNetProxy netGameSrv)
        {
            App.instance.panelMgr.HidePanel(UIPanelId.MainPanel);
        }

        void OnGameSrvClosed(string evName, CommonNetProxy evParam)
        {
            App.instance.panelMgr.ShowPanel(UIPanelId.MainPanel);
        }
    }
}
