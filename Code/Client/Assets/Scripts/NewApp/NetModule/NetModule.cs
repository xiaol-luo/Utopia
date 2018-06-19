using System.Collections.Generic;
using Utopia.Net;

namespace Utopia
{
    public class NetModule : AppModule
    {

        public static string ProtocolEventKey(int protoId)
        {
            string ret = string.Format(NetModuleEventDef.ProtocolEventKeyFormat, protoId);
            return ret;
        }
        public static EventId<string> SubscribeNetEvent(EventProxy<string> evProxy, int protoId, System.Action<string> cb)
        {
            string evKey = string.Format(NetModuleEventDef.ProtocolEventKeyFormat, protoId);
            var ret = evProxy.Subscribe(evKey, cb);
            return ret;
        }
        public static EventId<string> Subscribe<T>(EventProxy<string> evProxy, int protoId, System.Action<string, T> cb)
        {
            string evKey = string.Format(NetModuleEventDef.ProtocolEventKeyFormat, protoId);
            EventId<string> ret = evProxy.Subscribe(evKey, cb);
            return ret;
        }

        ulong m_lastId = 0;
        Dictionary<ulong, NetAgent> m_netAgents = new Dictionary<ulong, NetAgent>();

        public CommonNetProxy gameSrv { get; protected set; }

        public NetModule(NewApp _app) : base(_app, EModule.NetModule)
        {
           
        }

        public ulong AddNetAgent(NetAgent netAgent)
        {
            ++m_lastId;
            netAgent.id = m_lastId;
            m_netAgents.Add(m_lastId, netAgent);
            return m_lastId;
        }

        public void RemoveNetAgent(ulong id)
        {
            NetAgent na = this.GetNetAgent(id);
            m_netAgents.Remove(id);
            if (null != na)
            {
                app.eventModule.Fire(NetModuleEventDef.RemoveNetAgent, na);
            }
        }

        public NetAgent GetNetAgent(ulong id)
        {
            NetAgent ret = null;
            m_netAgents.TryGetValue(id, out ret);
            return ret;
        }

        protected override ERet OnStart()
        {
            {
                gameSrv = new CommonNetProxy();
                GameSrvNetAgentHandler nah = new GameSrvNetAgentHandler();
                nah.SetNetProxy(gameSrv);
                nah.Init();
                gameSrv.SetNetAgentHandler(nah);

                gameSrv.Connect("127.0.0.1", 10240);
            }

            return ERet.Success;
        }

        protected override void OnFixedUpdate()
        {
            base.OnFixedUpdate();

            List<ulong> toRemoveAgentIds = new List<ulong>();
            var tmpAgents = new Dictionary<ulong, NetAgent>(m_netAgents);
            foreach (var kvPair in tmpAgents)
            {
                ulong id = kvPair.Key;
                NetAgent na = kvPair.Value;

                if (ClientSocket.State.Connecting !=  na.socket.state ||
                    ClientSocket.State.Connected != na.socket.state)
                {
                    toRemoveAgentIds.Add(id);
                }
                na.UpdateIO();
            }
            foreach (ulong id in toRemoveAgentIds)
            {
                RemoveNetAgent(id);
            }
        }
    }
}
