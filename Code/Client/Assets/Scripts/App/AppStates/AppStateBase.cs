
namespace Utopia
{
    public enum EAppState
    {
        LiveUpdate, // 在线更新
        AwakeCore, // 唤醒Core
        WaitTask, // 等待任务
        InLogic, // 处理逻辑
        InBattle, // 战斗中
        Quit, // 退出

        Count,
    }

    public class AppStateBase : IState
    {
        public AppStateBase() : base(null, 0) { }
        public AppStateBase(IStateMgr stateMgr, int id) : base(stateMgr, id)
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

