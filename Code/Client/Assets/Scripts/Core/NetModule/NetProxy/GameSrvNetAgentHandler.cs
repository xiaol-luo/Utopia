using NetProto;

namespace Utopia.Net
{
    public class GameSrvNetAgentHandler : CommonNetAgentHandler
    {
        GameSrvNetProxy m_gsNetProxy;
        protected override void OnInit()
        {
            base.OnInit();
            m_gsNetProxy = m_netProxy as GameSrvNetProxy;
            m_gsNetProxy.Add<RspFreeHero>(ProtoId.PidRspFreeHero);
        }

        protected override void OnSockeClose(int errno, string errMsg)
        {
            base.OnSockeClose(errno, errMsg);
            Core.instance.eventModule.Fire(NetModuleEventDef.GameSrvNetClosed, m_gsNetProxy);
        }

        protected override void OnSocketOpen(bool isSucc)
        {
            base.OnSocketOpen(isSucc);
            Core.instance.eventModule.Fire(NetModuleEventDef.GameSrvNetConnected, m_gsNetProxy);
        }
    }
}