using System.Collections.Generic;

namespace Utopia
{
    public class EventProxy<EventKeyType>
    {
        HashSet<EventId<EventKeyType>> m_eventIdSet = new HashSet<EventId<EventKeyType>>();
        EventMgr<EventKeyType> m_mgr;

        public EventProxy(EventMgr<EventKeyType> mgr)
        {
            m_mgr = mgr;
        }

        public void ClearAll()
        {
            foreach (var eventId in m_eventIdSet)
            {
                m_mgr.Remove(eventId);
            }
            m_eventIdSet.Clear();
        }

        public void Remove(EventId<EventKeyType> eventId)
        {
            if (m_eventIdSet.Contains(eventId))
            {
                m_eventIdSet.Remove(eventId);
                m_mgr.Remove(eventId);
            }
        }

        public EventId<EventKeyType> Subscribe(EventKeyType eventKey, System.Action<EventKeyType> cb)
        {
            EventId<EventKeyType> ret = m_mgr.Subscribe(eventKey, cb);
            if (ret.IsValid())
            {
                m_eventIdSet.Add(ret);
            }
            return ret;
        }
        public EventId<EventKeyType> Subscribe<T>(EventKeyType eventKey, System.Action<EventKeyType, T> cb)
        {
            EventId<EventKeyType> ret = m_mgr.Subscribe(eventKey, cb);
            if (ret.IsValid())
            {
                m_eventIdSet.Add(ret);
            }
            return ret;
        }

        public void Fire(EventKeyType eventKey)
        {
            m_mgr.Fire(eventKey);
        }
        public void Fire(EventKeyType eventKey, object param)
        {
            m_mgr.Fire(eventKey, param);
        }
    }
}
