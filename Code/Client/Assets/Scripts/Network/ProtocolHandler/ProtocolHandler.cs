
using Google.Protobuf;
using System.Collections.Generic;

public class ProtocolHandler 
{
    Dictionary<int, IHandler> handlers = new Dictionary<int, IHandler>();
    public void OnMessage(int protocolId, byte[] data, int dataBegin, int dataLen)
    {
        IHandler handler = null;
        handlers.TryGetValue(protocolId, out handler);
        if (null != handler)
        {
            handler.OnMessage(protocolId, data, dataBegin, dataLen);
        }
    }

    public void Add<T>(int protocolId, System.Action<int, T> action) where T : IMessage, new()
    {
        Handler<T> handler = new Handler<T>(action);
        handlers.Add(protocolId, handler);
    }

    public void Add(int protocolId, System.Action<int> action)
    {
        Handler handler = new Handler(action);
        handlers.Add(protocolId, handler);
    }

    public void Remove(int protocolId)
    {
        handlers.Remove(protocolId);
    }

    interface IHandler
    {
        void OnMessage(int protocolId, byte[] data, int dataBegin, int dataLen);
    }

    internal class Handler : IHandler
    {
        System.Action<int> m_actioin;
        public Handler(System.Action<int> actioin)
        {
            m_actioin = actioin;
        }
        public void OnMessage(int protocolId, byte[] data, int dataBegin, int dataLen)
        {
            m_actioin(protocolId);
        }
    }

    class Handler<T> : IHandler where T : IMessage, new()
    {
        System.Action<int, T> m_actioin;
        public Handler(System.Action<int, T> actioin)
        {
            m_actioin = actioin;
        }
        public void OnMessage(int protocolId, byte[] data, int dataBegin, int dataLen)
        {
            T msg = new T();
            msg.MergeFrom(new CodedInputStream(data, dataBegin, dataLen));
            m_actioin(protocolId, msg);
        }
    }
}
