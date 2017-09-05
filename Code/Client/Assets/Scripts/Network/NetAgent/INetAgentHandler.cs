
public interface INetAgentHandler
{
    void OnOPen(bool isSucc);
    void OnRecvData(int protocolId, byte[]data, int dataBegin, int dataLen);
    void OnClose(int errno, string errMsg);
}

