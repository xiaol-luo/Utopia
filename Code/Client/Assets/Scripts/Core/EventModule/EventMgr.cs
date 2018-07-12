using System;
using System.Collections.Generic;

namespace Utopia
{
    public class EventId<EventKeyType>
    {
        public EventKeyType key;
        public ulong idx;
        public WeakReference mgr;
        public void Release()
        {
            if (this.IsValid() && null != mgr && mgr.IsAlive)
            {
                EventMgr<EventKeyType> refMgr = mgr.Target as EventMgr<EventKeyType>;
                if (null != refMgr)
                {
                    refMgr.Remove(this);
                    idx = 0;
                }
            }
        }

        public bool IsValid()
        {
            return idx > 0;
        }
    }

    public class EventCallback<EventKeyType>
    {
        public EventCallback(System.Action<EventKeyType> _cb)
        {
            cb = _cb;
        }
        public void Fire(EventKeyType key)
        {
            cb(key);
        }
        public virtual void Fire(EventKeyType key, object param)
        {
            cb(key);
        }

        public System.Action<EventKeyType> cb;
    }

    public class EventCallback<EventKeyType, T> : EventCallback<EventKeyType>
    {
        public EventCallback(Action<EventKeyType, T> _cb) : base(
            (EventKeyType key) => { _cb(key, default(T)); }
            )
        {
            cb2 = _cb;
        }
        public override void Fire(EventKeyType key, object param) 
        {
            if (param is T)
            {
                cb2(key, (T)param);
            }
            else
            {
                UnityEngine.Debug.LogErrorFormat("EventMgr Fire Error: key {0}, invalid cast param to {1}", 
                    key.ToString(), typeof(T).FullName);
            }
        }

        Action<EventKeyType, T> cb2;
    }

    public class EventCallbackMgr<EventKeyType>
    {
        public EventCallbackMgr(EventKeyType eventKey)
        {
            m_eventKey = eventKey;
        }

        EventKeyType m_eventKey;
        public const ulong Invalid_Id = 0;

        protected ulong lastId = 0;
        public Dictionary<ulong, EventCallback<EventKeyType> > cbs = new Dictionary<ulong, EventCallback<EventKeyType> >();

        public ulong AddCallback(EventCallback<EventKeyType> cb)
        {
            if (null == cb)
                return Invalid_Id;
            cbs.Add(++lastId, cb);
            return lastId;
        }
        public void RemoveCallback(ulong id)
        {
            cbs.Remove(id);
        }

        public void FireCallbacks()
        {
            List<EventCallback<EventKeyType> > tmp = new List<EventCallback<EventKeyType> >(cbs.Values);
            foreach (EventCallback<EventKeyType> cb in tmp)
            {
                cb.Fire(m_eventKey);
            }
        }
        public void FireCallbacks(object param)
        {
            List<EventCallback<EventKeyType>> tmp = new List<EventCallback<EventKeyType>>(cbs.Values);
            foreach (EventCallback<EventKeyType> cb in tmp)
            {
                cb.Fire(m_eventKey, param);
            }
        }
    }

    public class EventMgr<EventKeyType>
    {

        Dictionary<EventKeyType, EventCallbackMgr<EventKeyType> > m_eventCbMgrs = new Dictionary<EventKeyType, EventCallbackMgr<EventKeyType> >();

        public EventId<EventKeyType> Subscribe(EventKeyType eventKey, System.Action<EventKeyType> cb)
        {
            EventCallback<EventKeyType> ecb = new EventCallback<EventKeyType>(cb);
            EventId<EventKeyType> ret = this.DoSubscribe(eventKey, ecb);
            return ret;
        }
        public EventId<EventKeyType> Subscribe<T>(EventKeyType eventKey, System.Action<EventKeyType, T > cb)
        {
            EventCallback<EventKeyType> ecb = new EventCallback<EventKeyType, T>(cb); ;
            EventId<EventKeyType> ret = this.DoSubscribe(eventKey, ecb);
            return ret;
        }

        protected EventId<EventKeyType> DoSubscribe(EventKeyType eventKey, EventCallback<EventKeyType> ecb)
        {
            EventCallbackMgr<EventKeyType> cbMgr = null;
            if (!m_eventCbMgrs.TryGetValue(eventKey, out cbMgr))
            {
                cbMgr = new EventCallbackMgr<EventKeyType>(eventKey);
                m_eventCbMgrs.Add(eventKey, cbMgr);
            }
            ulong eid = cbMgr.AddCallback(ecb);
            EventId<EventKeyType> ret = new EventId<EventKeyType>();
            ret.key = eventKey;
            ret.idx = eid;
            ret.mgr = new WeakReference(this);
            return ret;
        }

        public void Remove(EventId<EventKeyType> eventId)
        {
            EventCallbackMgr<EventKeyType> cbMgr = null;
            if (m_eventCbMgrs.TryGetValue(eventId.key, out cbMgr))
            {
                cbMgr.RemoveCallback(eventId.idx);
            }
        }

        public void ClearAll()
        {
            m_eventCbMgrs.Clear();
        }

        public void Fire(EventKeyType eventKey)
        {
            EventCallbackMgr<EventKeyType> cbMgr = null;
            if (m_eventCbMgrs.TryGetValue(eventKey, out cbMgr))
            {
                cbMgr.FireCallbacks();
            }
        }
        public void Fire(EventKeyType eventKey, object param)
        {
            EventCallbackMgr<EventKeyType> cbMgr = null;
            if (m_eventCbMgrs.TryGetValue(eventKey, out cbMgr))
            {
                cbMgr.FireCallbacks(param);
            }
        }
    }
}