using System.Collections.Generic;
using Utopia.Net;

namespace Utopia
{
    public class NetModule : CoreModule
    {
        ulong m_lastId = 0;
        Dictionary<ulong, NetAgent> m_netAgents = new Dictionary<ulong, NetAgent>();

        public NetModule(Core _app) : base(_app, EModule.NetModule)
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
                app.eventMgr.Fire(NetModuleEventDef.RemoveNetAgent, na);
            }
        }

        public NetAgent GetNetAgent(ulong id)
        {
            NetAgent ret = null;
            m_netAgents.TryGetValue(id, out ret);
            return ret;
        }

        protected override void OnUpdate()
        {
            base.OnUpdate();

            List<ulong> toRemoveAgentIds = new List<ulong>();
            var tmpAgents = new Dictionary<ulong, NetAgent>(m_netAgents);
            foreach (var kvPair in tmpAgents)
            {
                ulong id = kvPair.Key;
                NetAgent na = kvPair.Value;

                if (null == na.socket ||
                    ClientSocket.State.Error ==  na.socket.state ||
                    ClientSocket.State.Free == na.socket.state)
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

