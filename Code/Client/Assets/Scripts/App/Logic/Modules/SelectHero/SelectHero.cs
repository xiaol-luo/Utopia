using UnityEngine;
using UnityEditor;
using Utopia.Net;
using Utopia.UI;
using Utopia;
using System.Collections.Generic;

namespace Utopia.Logic
{
    public class SelectHero : LogicBase
    {
        public override ELogicName GetModuleName()
        {
            return ELogicName.SelectHero;
        }

        public ulong usingHeroObjId { get; protected set; }
        public ulong redHeroId = 0;
        public ulong blueHeroId = 0;

        protected override void OnAwake()
        {
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetConnected, OnGameSrvConnected);
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetClosed, OnGameSrvClosed);
            m_evProxy.Subscribe<NetProto.RspFreeHero>(
                GameSrvNetProxy.ProtoEventName(NetProto.ProtoId.PidRspFreeHero), OnRspFreeHero);
            m_evProxy.Subscribe<NetProto.SelectHeroRsp>(
                GameSrvNetProxy.ProtoEventName(NetProto.ProtoId.PidSelectHeroRsp), OnRspSelectHero);
        }

        protected override void OnInit()
        {
            usingHeroObjId = 0;
        }

        protected override void OnRelease()
        {

        }

        void OnGameSrvConnected(string evName, CommonNetProxy netGameSrv)
        {
            bool isConnected = (0 == netGameSrv.netAgent.socket.errno);
            if (isConnected && usingHeroObjId > 0)
            {
                this.SelectHeroReq(usingHeroObjId);
                App.instance.panelMgr.ShowPanel(UIPanelId.SelectHeroPanel);
            }
            else
            {
                App.instance.panelMgr.ShowPanel(UIPanelId.MainPanel);
            }
        }

        void OnGameSrvClosed(string evName, CommonNetProxy evParam)
        {

        }

        public void QueryFreeHero()
        {
            App.instance.net.gameSrv.Send(NetProto.ProtoId.PidQueryFreeHero);
        }

        public void SelectHeroReq(ulong uid)
        {
            NetProto.SelectHeroReq req = new NetProto.SelectHeroReq() { HeroId = uid };
            App.instance.net.gameSrv.Send(NetProto.ProtoId.PidSelectHeroReq, req);
        }

        void OnRspFreeHero(string evName, NetProto.RspFreeHero msg)
        {
            redHeroId = msg.RedHeroId;
            blueHeroId = msg.BlueHeroId;
            m_evProxy.Fire(SelectHeroModuleDef.Event_OnRspFreeHeros);
        }

        void OnRspSelectHero(string evName, NetProto.SelectHeroRsp msg)
        {
            if (msg.IsSucc)
            {
                usingHeroObjId = msg.HeroId;
                Core.instance.log.LogDebug("OnRspSelectHero succ");
            }
            else
            {
                usingHeroObjId = 0;
            }
            m_evProxy.Fire(SelectHeroModuleDef.Event_OnRspSelectHero);
            this.QueryFreeHero();
        }
    }
}
