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

        public ulong id
        {
            get
            {
                var ret = (null != req) ? req.id : 0;
                return ret;
            }
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
        public ResourceObserver AddObserver(System.Action<string, ResourceObserver> cb)
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

        int m_refCount = 0;
        public int refCount { get { return m_refCount; } }
        public void AddRef() { ++m_refCount; }
        public void SubRef()
        {
            --m_refCount;
            if (null != loader)
            {
                loader.CheckUnloadRes(path, id);
            }
        }

        public T Instantiate<T>(UnityEngine.Vector3 position,  UnityEngine.Quaternion rotation) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != res)
            {
                ret = UnityEngine.GameObject.Instantiate<T>(res as T, position, rotation);
            }
            bool isOk = AttachMonitorRefMono(ret);
            return isOk ? ret : null;
        }

        public T Instantiate<T>(UnityEngine.Transform parent, bool worldPositionStays) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != res)
            {
                ret = UnityEngine.GameObject.Instantiate<T>(res as T, parent, worldPositionStays);
            }
            bool isOk = AttachMonitorRefMono(ret);
            return isOk ? ret : null;
        }
        public T Instantiate<T>(UnityEngine.Transform parent) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != res)
            {
                ret = UnityEngine.GameObject.Instantiate<T>(res as T, parent);
            }
            bool isOk = AttachMonitorRefMono(ret);
            return isOk ? ret : null;
        }
        public T Instantiate<T>(UnityEngine.Vector3 position, UnityEngine.Quaternion rotation, UnityEngine.Transform parent) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != res)
            {
                ret = UnityEngine.GameObject.Instantiate<T>(res as T, position, rotation, parent);
            }
            bool isOk = AttachMonitorRefMono(ret);
            return isOk ? ret : null;
        }
        public T Instantiate<T>() where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != res)
            {
                ret = UnityEngine.GameObject.Instantiate<T>(res as T);
            }
            bool isOk = AttachMonitorRefMono(ret);
            return isOk ? ret : null;
        }

        protected bool AttachMonitorRefMono<T>(T obj)
        {
            if (null == obj)
                return false;

            UnityEngine.GameObject go = null;
            if (obj is UnityEngine.Component)
            {
                go = (obj as UnityEngine.Component).gameObject;
            }
            if (obj is UnityEngine.GameObject)
            {
                go = (obj as UnityEngine.GameObject);
            }
            if (null != go)
            {
                Resource.GameObjectRefMonitorMono.Add(go, this);
            }
            else
            {
                Core.instance.logModule.LogDebug("AttachMonitorRefMono {0} is not the fit type", typeof(T));
            }
            return null != go;
        }
    }
}

