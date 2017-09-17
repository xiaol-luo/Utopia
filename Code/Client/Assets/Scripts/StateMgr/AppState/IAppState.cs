
public class IAppState : IState
{
    public enum StateName
    {
        Launch,
        SelectHero,
        LoadingScene,
        InBattle,
        Loading,

        Max,
    }

    public IAppState() : base(null, 0) { }
    public IAppState(IStateMgr stateMgr, int id) : base(stateMgr, id)
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