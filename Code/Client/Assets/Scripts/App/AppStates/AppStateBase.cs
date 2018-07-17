
namespace Utopia
{
    public enum EAppState
    {
        LiveUpdate, // ���߸���
        AwakeCore, // ����Core
        WaitTask, // �ȴ�����
        InLogic, // �����߼�
        InBattle, // ս����
        Quit, // �˳�

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

