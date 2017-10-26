
public class AppStateInBattle : IAppState
{
    public AppStateInBattle(IStateMgr stateMgr) : base(stateMgr, (int)IAppState.StateName.InBattle)
    {

    }

    public override void Enter(params object[] objs)
    {
        string sceneName = objs[0] as string;
        App.my.scene.EnterScene(sceneName);
    }

    public override void Exit(params object[] objs)
    {

    }

    public override void Update(params object[] objs)
    {

    }
}