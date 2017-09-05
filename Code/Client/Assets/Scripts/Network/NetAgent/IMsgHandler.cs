using Google.Protobuf;
public interface INetMsgHandler
{
    void OnMessage(int protocolId, byte[] data, int dataBegin, int dataLen);
}
public class NetMsgHandler : INetMsgHandler
{
    System.Action<int> m_actioin;
    public NetMsgHandler(System.Action<int> actioin)
    {
        m_actioin = actioin;
    }
    public void OnMessage(int protocolId, byte[] data, int dataBegin, int dataLen)
    {
        m_actioin(protocolId);
    }
}
public class NetMsgHandler<T> : INetMsgHandler where T : IMessage, new()
{
    System.Action<int, T> m_actioin;
    public NetMsgHandler(System.Action<int, T> actioin)
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
