
public class AppStateMgr : StateMgr<AppStateBase>
{
    public AppStateMgr()
    {
        this.AddState(new AppStateLaunch(this));
        this.AddState(new AppStateLoading(this));
        this.AddState(new AppStateSelectHero(this));
        this.AddState(new AppStateInBattle(this));
        this.AddState(new AppStateLoadingScene(this));
    }
}
