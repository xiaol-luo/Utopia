
namespace Utopia
{
    public enum EAppState
    {
        Invalid = 0,
        LiveUpdate, // ���߸���
        AwakeCore, // ����Core
        AwakeLua, // ����Lua
        WaitTask, // �ȴ�����
        InLogic, // �����߼�
        InBattle, // ս����
        Quit, // �˳�

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

