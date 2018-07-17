
using System;
using Utopia;

namespace Utopia
{
    public class AppStateWaitTask : AppStateBase
    {
        public AppStateWaitTask(IStateMgr stateMgr) : base(stateMgr, (int)EAppState.WaitTask)
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
            if (null != m_task)
            {
                Action task = m_task;
                m_task = null;
                task();
            }
        }

        Action m_task = null;
        public void SetTask(Action task)
        {
            m_task = task;
        }
    }
}

