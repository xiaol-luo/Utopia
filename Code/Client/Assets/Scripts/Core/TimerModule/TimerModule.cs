using System;
using System.Collections.Generic;
using UnityEngine;

namespace Utopia
{
    using TimerId = System.UInt64;

    public class TimerModule : CoreModule
    {
        TimerMgr m_timerMgr;
        public TimerModule(Core _app) : base(_app, EModule.TimerModule)
        {
            
        }
        protected override void OnInit()
        {
            base.OnInit();
            m_timerMgr = new TimerMgr(() => { return app.datetime.now; });
        }
        
        protected override void OnUpdate()
        {
            m_timerMgr.CheckTrigger();
        }

        public TimerProxy CreateTimerProxy()
        {
            TimerProxy ret = new TimerProxy(m_timerMgr);
            return ret;
        }

        public ulong Add(System.Action cb, float delaySec, int callTimes, float callSpanSec)
        {
            return m_timerMgr.Add(cb, delaySec, callTimes, callSpanSec);
        }

        public ulong Add(System.Action cb, float delaySec)
        {
            return m_timerMgr.Add(cb, delaySec);
        }

        public ulong Add(System.Action cb, int callTimes, float spanSec)
        {
            return m_timerMgr.Add(cb, callTimes, spanSec);
        }

        public void Remove(ulong id)
        {
            m_timerMgr.Remove(id);
        }

        public void ClearAll()
        {
            m_timerMgr.ClearAll();
        }
    }
}

