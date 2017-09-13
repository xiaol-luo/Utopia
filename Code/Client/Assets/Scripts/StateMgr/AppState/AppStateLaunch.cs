
public class AppStateLaunch : IAppState
{
    public AppStateLaunch(IStateMgr stateMgr) : base(stateMgr, (int)IAppState.StateName.Launch)
    {

    }

    public override void Enter(params object[] objs)
    {

    }

    public override void Exit(params object[] objs)
    {

    }

    public override void Update(params object[] objs)
    {

    }
}