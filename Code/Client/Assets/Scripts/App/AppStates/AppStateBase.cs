
public class AppStateBase : IState
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

    public AppStateBase() : base(null, 0) { }
    public AppStateBase(IStateMgr stateMgr, int id) : base(stateMgr, id)
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