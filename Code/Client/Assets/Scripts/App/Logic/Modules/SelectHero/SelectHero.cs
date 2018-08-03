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
        public enum SelectedSide
        {
            None,
            RedSide,
            BlueSide,
        }

        public override ELogicName GetModuleName()
        {
            return ELogicName.SelectHero;
        }

        public ulong usingHeroObjId { get; protected set; }
        public ulong redHeroId = 0;
        public ulong blueHeroId = 0;

        SelectedSide m_selctedSide = SelectedSide.None;

        protected override void OnAwake()
        {
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetConnected, OnGameSrvConnected);
            m_evProxy.Subscribe<CommonNetProxy>(NetModuleEventDef.GameSrvNetClosed, OnGameSrvClosed);
            m_evProxy.Subscribe<NetProto.RspFreeHero>(
                GameSrvNetProxy.ProtoEventName(NetProto.PID.RspFreeHero), OnRspFreeHero);
            m_evProxy.Subscribe<NetProto.SelectHeroRsp>(
                GameSrvNetProxy.ProtoEventName(NetProto.PID.SelectHeroRsp), OnRspSelectHero);
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
            usingHeroObjId = 0;
            this.QueryFreeHero();
        }

        void OnGameSrvClosed(string evName, CommonNetProxy evParam)
        {
            App.instance.panelMgr.HidePanel(UIPanelId.SelectHeroPanel);
        }

        public void QueryFreeHero()
        {
            App.instance.net.gameSrv.Send(NetProto.PID.QueryFreeHero);
        }

        public void SelectHeroReq(ulong uid)
        {
            NetProto.SelectHeroReq req = new NetProto.SelectHeroReq() { HeroId = uid };
            App.instance.net.gameSrv.Send(NetProto.PID.SelectHeroReq, req);
        }

        void OnRspFreeHero(string evName, NetProto.RspFreeHero msg)
        {
            redHeroId = msg.RedHeroId;
            blueHeroId = msg.BlueHeroId;
            m_evProxy.Fire(SelectHeroModuleDef.Event_OnRspFreeHeros);

            if (usingHeroObjId <= 0)
            {
                bool needShowPanel = true;
                switch (m_selctedSide)
                {
                    case SelectedSide.RedSide:
                        {
                            if (redHeroId > 0)
                            {
                                this.SelectHeroReq(redHeroId);
                                needShowPanel = false;
                            }
                        }
                        break;
                    case SelectedSide.BlueSide:
                        {
                            if (blueHeroId > 0)
                            {
                                this.SelectHeroReq(blueHeroId);
                                needShowPanel = false;
                            }
                        }
                        break;
                }
                if (needShowPanel)
                {
                    App.instance.panelMgr.ShowPanel(UIPanelId.SelectHeroPanel);
                }
            }
        }

        void OnRspSelectHero(string evName, NetProto.SelectHeroRsp msg)
        {
            if (msg.IsSucc)
            {
                usingHeroObjId = msg.HeroId;
                Core.instance.log.LogDebug("OnRspSelectHero succ");
                App.instance.panelMgr.HidePanel(UIPanelId.SelectHeroPanel);
                if (App.instance.stateMgr.activeId != EAppState.InBattle)
                {
                    App.instance.stateMgr.ChangeState(EAppState.InBattle);
                }
            }
            else
            {
                usingHeroObjId = 0;
                m_selctedSide = SelectedSide.None;
                this.QueryFreeHero();
            }
            m_evProxy.Fire(SelectHeroModuleDef.Event_OnRspSelectHero);
        }

        public void SelectSide(SelectedSide side)
        {
            if (usingHeroObjId > 0)
            {
                if (side != m_selctedSide)
                {
                    this.SelectHeroReq(0);
                    usingHeroObjId = 0;
                    m_selctedSide = side;
                }
            }
            else
            {
                m_selctedSide = side;
                this.QueryFreeHero();
            }
        }
    }
}
