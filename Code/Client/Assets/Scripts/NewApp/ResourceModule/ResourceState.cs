using System;
using System.Collections;
using System.Collections.Generic;

namespace Utopia
{
    
    public class ResourceState
    {
        public ResourceState(ResourceLoader _loader)
        {
            loader = _loader;
        }

        public string path
        {
            get
            {
                var ret = (null != req) ? req.path : string.Empty;
                return ret;

            }
        }

        public UnityEngine.Object res
        {
            get
            {
                var ret = (null != req) ? req.res : null;
                return ret;
            }
        }

        public bool isValid
        {
            get
            {
                if (null == req)
                    return false;
                if (req.isUnloaded)
                    return false;
                return true;
            }
        }

        public bool isDone
        {
            get
            {
                var ret = (null != req) ? req.isDone : false;
                return ret;
            }
        }

        public bool isLoaded
        {
            get
            {
                var ret = (null != req) ? req.isLoaded : false;
                return ret;
            }
        }

        public bool isLoadFail
        {
            get
            {
                var ret = (null != req) ? req.isLoadFail : false;
                return ret;
            }
        }

        public bool isUnloaded
        {
            get
            {
                var ret = (null != req) ? req.isUnloaded : false;
                return ret;
            }
        }

        public ResourceLoader loader;
        public ResourceRequest req;

        uint m_lastObserverId = 0;
        Dictionary<uint, ResourceObserver> m_observers = new Dictionary<uint, ResourceObserver>();
        public ResourceObserver AddObserver(System.Action<string, UnityEngine.Object> cb)
        {
            ++m_lastObserverId;
            ResourceObserver ob = new ResourceObserver(cb);
            ob.id = m_lastObserverId;
            ob.resState = this;
            m_observers.Add(ob.id, ob);
            return ob;
        }
        public void RemoveObserver(uint obId)
        {
            ResourceObserver ob;
            if (m_observers.TryGetValue(obId, out ob))
            {
                m_observers.Remove(obId);
                ob.ResetAll();
                loader.CheckUnloadRes(req.path, req.id);
            }
        }
        public void RemoveObserver(ResourceObserver ob)
        {
            if (null != ob)
                this.RemoveObserver(ob.id);
        }

        public List<ResourceObserver> GetObservers()
        {
            return new List<ResourceObserver>(m_observers.Values);
        }
        public int observerCount
        {
            get { return m_observers.Count; }
        }
    }
}

