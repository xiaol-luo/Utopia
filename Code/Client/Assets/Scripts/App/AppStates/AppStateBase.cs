
namespace Utopia
{
    public enum EAppState
    {
        Invalid = 0,
        LiveUpdate, // 在线更新
        AwakeCore, // 唤醒Core
        AwakeLua, // 唤醒Lua
        WaitTask, // 等待任务
        InLogic, // 处理逻辑
        InBattle, // 战斗中
        Quit, // 退出

        Count,
    }

    public class AppStateBase : IState<EAppState>
    {
        public AppStateBase() : base(null, 0) { }
        public AppStateBase(AppStateMgr stateMgr, EAppState id) : base(stateMgr, id)
        {

        }
        public override void Enter(object param)
        {
        }

        public override void Exit()
        {
        }

        public override void Update()
        {
        }
    }
}

