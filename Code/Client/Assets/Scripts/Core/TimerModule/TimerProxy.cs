using System;
using System.Collections.Generic;

namespace Utopia
{
    public class TimerProxy
    {
        TimerMgr m_mgr;
        HashSet<ulong> m_timerIds = new HashSet<ulong>();
        public TimerProxy(TimerMgr mgr)
        {
            m_mgr = mgr;
        }
        
        public ulong Add(System.Action cb, float delaySec, int callTimes, float callSpanSec)
        {
            ulong timerId = m_mgr.Add(cb, delaySec, callTimes, callSpanSec);
            if (timerId > 0)
                m_timerIds.Add(timerId);
            return timerId;
        }

        public ulong Add(System.Action cb, float delaySec)
        {
            return this.Add(cb, delaySec, 1, 0);
        }

        public ulong Add(System.Action cb, int callTimes, float spanSec)
        {
            return this.Add(cb, 0, callTimes, spanSec);
        }

        public void Remove(ulong id)
        {
            if (m_timerIds.Contains(id))
            {
                m_mgr.Remove(id);
                m_timerIds.Remove(id);
            }
        }

        public void ClearAll()
        {
            foreach (ulong id in m_timerIds)
            {
                m_mgr.Remove(id);
            }
            m_timerIds.Clear();
        }
    }
}

