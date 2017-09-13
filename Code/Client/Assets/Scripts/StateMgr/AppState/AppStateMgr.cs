
public class AppStateMgr : StateMgr<IAppState>
{
    public AppStateMgr()
    {
        this.AddState(new AppStateLaunch(this));
        this.AddState(new AppStateLoading(this));
    }
}
