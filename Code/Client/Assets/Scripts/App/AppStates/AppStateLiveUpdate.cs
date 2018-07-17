
using System;
using Utopia;

namespace Utopia
{
    public class AppStateLiveUpdate : AppStateBase
    {
        public AppStateLiveUpdate(IStateMgr stateMgr) : base(stateMgr, (int)EAppState.LiveUpdate)
        {

        }

        public override void Enter(object param)
        {
            this.CheckInit();
        }

        public override void Exit()
        {

        }

        public override void Update()
        {
            // for test
            if (!m_isDone)
            {
                m_isDone = true;
            }
            if (m_isDone)
            {
                m_stateMgr.ChangeState(EAppState.AwakeCore, null);
            }
        }

        bool m_isInited = false;
        bool m_isDone = false;
        void CheckInit()
        {
            if (m_isInited)
            {
                m_isInited = true;
            }
        }
    }
}
