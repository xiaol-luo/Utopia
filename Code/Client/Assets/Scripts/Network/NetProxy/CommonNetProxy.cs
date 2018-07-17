using Google.Protobuf;
using System.Collections.Generic;

namespace Utopia.Net
{
    public class CommonNetProxy
    {
        protected NetAgent m_netAgent;
        public NetAgent netAgent { get { return m_netAgent; } }
        protected EventProxy<string> m_evProxy;
        public EventProxy<string> evProxy { get { return m_evProxy; } }

        public CommonNetProxy()
        {
            m_netAgent = new NetAgent();
            m_evProxy = Core.instance.eventMgr.CreateEventProxy();
            m_evProxy.Subscribe<NetAgent>(NetModuleEventDef.RemoveNetAgent, this.OnNetAgentError);
        }

        public void SetNetAgentHandler(INetAgentHandler netAgentHandler)
        {
            m_netAgent.SetHandler(netAgentHandler);
        }

        void OnNetAgentError(string evName, NetAgent na)
        {

        }
        public void Connect(string ip, int port)
        {
            Core.instance.net.RemoveNetAgent(m_netAgent.id);
            m_netAgent.id = 0;
            if (m_netAgent.Connect(ip, port))
            {
                Core.instance.net.AddNetAgent(m_netAgent);
            }
        }
        public void Reconnect()
        {
            Core.instance.net.RemoveNetAgent(m_netAgent.id);
            if (m_netAgent.ReConnect())
            {
                Core.instance.net.AddNetAgent(m_netAgent);
            }
        }
        public void Close()
        {
            m_netAgent.Close();
        }
        public bool Send(byte[] data, int offset, int len)
        {
            return m_netAgent.Send(data, offset, len);
        }
        public bool Send(int protocolId, IMessage msg)
        {
            return m_netAgent.Send(protocolId, msg);
        }
        public bool Send(int protocolId)
        {
            return m_netAgent.Send(protocolId);
        }
        public bool Send(NetProto.ProtoId protocolId, IMessage msg)
        {
            return m_netAgent.Send((int)protocolId, msg);
        }
        public bool Send(NetProto.ProtoId protocolId)
        {
            return m_netAgent.Send((int)protocolId);
        }

        protected Dictionary<int, INetMsgHandler> msgHandlers = new Dictionary<int, INetMsgHandler>();
        public void Add<T>(int protocolId, System.Action<int, T> action) where T : IMessage, new()
        {
            NetMsgHandler<T> handler = new NetMsgHandler<T>(action);
            msgHandlers.Add(protocolId, handler);
        }
        public void Add(int protocolId, System.Action<int> action)
        {
            NetMsgHandler handler = new NetMsgHandler(action);
            msgHandlers.Add(protocolId, handler);
        }
        public void Add<T>(int protocolId) where T : IMessage, new()
        {
            NetMsgHandler<T> handler = new NetMsgHandler<T>(DefaultMsgHandlerAction);
            msgHandlers.Add(protocolId, handler);
        }
        public void Add(int protocolId)
        {
            NetMsgHandler handler = new NetMsgHandler(DefaultMsgHandlerAction);
            msgHandlers.Add(protocolId, handler);
        }
        public virtual void DefaultMsgHandlerAction(int protocolId)
        {
            string evKey = string.Format(NetModuleEventDef.ProtocolEventKeyFormat, protocolId);
            m_evProxy.Fire(evKey);
        }
        public virtual void DefaultMsgHandlerAction<T>(int protocolId, T msg) where T : IMessage, new()
        {
            string evKey = string.Format(NetModuleEventDef.ProtocolEventKeyFormat, protocolId);
            m_evProxy.Fire(evKey, msg);
        }

        public void Remove(int protocolId)
        {
            msgHandlers.Remove(protocolId);
        }

        public INetMsgHandler GetMsgHandler(int protocolId)
        {
            INetMsgHandler ret = null;
            msgHandlers.TryGetValue(protocolId, out ret);
            return ret;
        }
    }
}