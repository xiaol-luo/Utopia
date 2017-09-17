using Google.Protobuf;
using System.Collections.Generic;

public class GameNetwork : INetAgentHandler
{
    NetAgent m_netAgent = new NetAgent();
    public string host { get { return m_netAgent.host; } }
    public int port { get { return m_netAgent.port; } }
    public GameNetwork()
    {
        m_netAgent.SetHandler(this);
    }
    public bool Connect(string _host, int _port)
    {
        return m_netAgent.Connect(_host, _port);
    }
    public bool ReConnect()
    {
        return m_netAgent.ReConnect();
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
    public void UpdateIO()
    {
        m_netAgent.UpdateIO();
    }
    Dictionary<int, INetMsgHandler> handlers = new Dictionary<int, INetMsgHandler>();
    public void Add<T>(int protocolId, System.Action<int, T> action) where T : IMessage, new()
    {
        NetMsgHandler<T> handler = new NetMsgHandler<T>(action);
        handlers.Add(protocolId, handler);
    }
    public void Add(int protocolId, System.Action<int> action)
    {
        NetMsgHandler handler = new NetMsgHandler(action);
        handlers.Add(protocolId, handler);
    }
    public void Remove(int protocolId)
    {
        handlers.Remove(protocolId);
    }

    public delegate void OpenCb(bool isSucc);
    public event OpenCb openCb;
    public delegate void CloseCb(int errno, string errMsg);
    public event CloseCb closeCb;
    void INetAgentHandler.OnOpen(bool isSucc)
    {
        if (null != openCb)
            openCb(isSucc);
    }
    void INetAgentHandler.OnRecvData(int protocolId, byte[] data, int dataBegin, int dataLen)
    {
        INetMsgHandler handler = null;
        handlers.TryGetValue(protocolId, out handler);
        if (null != handler)
        {
            handler.OnMessage(protocolId, data, dataBegin, dataLen);
        }
    }
    void INetAgentHandler.OnClose(int errno, string errMsg)
    {
        if (null != closeCb)
            closeCb(errno, errMsg);
    }
}


