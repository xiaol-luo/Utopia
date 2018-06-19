namespace Utopia.Net
{
    public class GameSrvNetAgentHandler : CommonNetAgentHandler
    {
        protected override void OnInit()
        {
            base.OnInit();
        }

        protected override void OnSockeClose(int errno, string errMsg)
        {
            base.OnSockeClose(errno, errMsg);
        }

        protected override void OnSocketOpen(bool isSucc)
        {
            base.OnSocketOpen(isSucc);
        }
    }
}