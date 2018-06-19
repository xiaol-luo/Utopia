namespace Utopia.Net
{
    public class CommonNetAgentHandler : INetAgentHandler
    {
        CommonNetProxy m_netProxy;
        public void SetNetProxy(CommonNetProxy netProxy)
        {
            m_netProxy = netProxy;
        }

        public void Init()
        {
            this.OnInit();
        }

        void INetAgentHandler.OnRecvData(int protocolId, byte[] data, int dataBegin, int dataLen)
        {
            INetMsgHandler handler = m_netProxy.GetMsgHandler(protocolId);
            if (null != handler)
            {
                handler.OnMessage(protocolId, data, dataBegin, dataLen);
            }
        }
        void INetAgentHandler.OnClose(int errno, string errMsg)
        {
            this.OnSockeClose(errno, errMsg);
            m_netProxy.evProxy.Fire(NetModuleEventDef.CommonNetClose, this);
        }

        void INetAgentHandler.OnOpen(bool isSucc)
        {
            this.OnSocketOpen(isSucc);
            m_netProxy.evProxy.Fire(NetModuleEventDef.CommonNetConnect, this);
        }

        protected virtual void OnInit()
        {

        }

        protected virtual void OnSockeClose(int errno, string errMsg)
        {

        }

        protected virtual void OnSocketOpen(bool isSucc)
        {

        }
    }
}