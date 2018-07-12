namespace Utopia
{
    public class EventModule : CoreModule
    {
        public EventMgr<string> m_eventMgr = new EventMgr<string>();

        public EventModule(Core _app) : base(_app, EModule.EventModule)
        {

        }

        public EventProxy<string> CreateEventProxy()
        {
            EventProxy <string> ret = new EventProxy<string>(m_eventMgr);
            return ret;
        }
        public void Remove(EventId<string> eventId)
        {
            m_eventMgr.Remove(eventId);
        }
        public void ClearAll()
        {
            m_eventMgr.ClearAll();
        }
        public EventId<string> Subscribe(string eventKey, System.Action<string> cb)
        {
            var ret = m_eventMgr.Subscribe(eventKey, cb);
            return ret;
        }
        public EventId<string> Subscribe<T>(string eventKey, System.Action<string, T> cb)
        {
            var ret = m_eventMgr.Subscribe(eventKey, cb);
            return ret;
        }
        public void Fire(string eventKey)
        {
            m_eventMgr.Fire(eventKey);
        }
        public void Fire(string eventKey, object param)
        {
            m_eventMgr.Fire(eventKey, param);
        }
    }
}

