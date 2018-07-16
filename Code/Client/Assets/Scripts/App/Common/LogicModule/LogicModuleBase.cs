using UnityEngine;
using UnityEditor;

namespace Utopia
{
    public abstract class LogicModuleBase
    {
        protected EventProxy<string> m_evProxy = Core.instance.eventMgr.CreateEventProxy();
        protected TimerProxy m_timer = Core.instance.timer.CreateTimerProxy();

        public abstract ELogicModule GetModuleName();
        protected abstract void OnInit();
        protected abstract void OnAwake();
        protected abstract void OnRelease();

        public void Init()
        {
            this.OnInit();
        }

        public void Awake()
        {
            this.OnAwake();
        }

        public void Release()
        {
            this.OnRelease();
            m_evProxy.ClearAll();
            m_timer.ClearAll();
        }

    }
}
