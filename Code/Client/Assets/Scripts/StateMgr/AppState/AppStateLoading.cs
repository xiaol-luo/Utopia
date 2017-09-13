
public class AppStateLoading : IAppState
{
    public AppStateLoading(IStateMgr stateMgr) : base(stateMgr, (int)IAppState.StateName.Loading)
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