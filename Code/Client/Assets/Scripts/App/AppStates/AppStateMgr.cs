
namespace Utopia
{
    public class AppStateMgr : StateMgr<AppStateBase>
    {
        public AppStateMgr()
        {
            this.AddState(new AppStateLiveUpdate(this));
            this.AddState(new AppStateAwakeCore(this));
            this.AddState(new AppStateWaitTask(this));
            this.AddState(new AppStateInLogic(this));
            this.AddState(new AppStateInBattle(this));
            this.AddState(new AppStateQuit(this));
        }
    }
}

