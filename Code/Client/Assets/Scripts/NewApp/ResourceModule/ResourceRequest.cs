using System;
using System.Collections;
using System.Collections.Generic;

namespace Utopia
{
    public class ResourceRequest : IEnumerator
    {
        public static ResourceRequest CreateAsyncRequest(IResourceLoaderImpl _loaderImpl, string path, System.Action<ResourceRequest> cb, ulong id)
        {
            ResourceRequest ret = new ResourceRequest();
            ret.loaderImpl = _loaderImpl;
            ret.id = id;
            ret.loadEndCb = cb;
            ret.path = path;
            ret.m_state = RequestState.Inited;
            return ret;
        }

        public static ResourceRequest CreateRequest(IResourceLoaderImpl _loaderImpl, string path, UnityEngine.Object res, ulong id)
        {
            ResourceRequest ret = new ResourceRequest();
            ret.loaderImpl = _loaderImpl;
            ret.id = id;
            ret.path = path;
            ret.res = res;
            ret.m_state = RequestState.Loaded;
            return ret;
        }

        enum RequestState
        {
            Invalid,
            Inited,
            Loading,
            Loaded,
            Fail,
            Unloaded,
        }

        public IResourceLoaderImpl loaderImpl;
        public ulong id;
        public UnityEngine.Object res { get; protected set; }
        public string path { get; protected set; }

        System.Action<ResourceRequest> loadEndCb = null;

        RequestState m_state = RequestState.Invalid;
        public bool isDone {
            get
            {
                bool ret = true;
                switch (m_state)
                {
                    case RequestState.Inited:
                    case RequestState.Loading:
                        ret = false;
                        break;
                }
                return ret;
            }
        }

        public bool isLoaded
        {
            get
            {
                bool ret = RequestState.Loaded == m_state;
                return ret;
            }
        }

        public bool isLoadFail
        {
            get
            {
                bool ret = RequestState.Fail == m_state;
                return ret;
            }
        }

        public bool isUnloaded
        {
            get
            {
                bool ret = RequestState.Unloaded == m_state;
                return ret;
            }
        }

        object IEnumerator.Current { get { return res; } }

        bool IEnumerator.MoveNext()
        {
            return !isDone;
        }

        void IEnumerator.Reset()
        {
            throw new System.NotImplementedException();
        }

        public void AsyncLoad()
        {
            loaderImpl.AsyncLoad(path,(UnityEngine.Object res) => {
                this.AsyncLoadEndCall(this, res);
            });
        }
        public void UnloadRes()
        {
            if (isDone && !isUnloaded)
            {
                m_state = RequestState.Unloaded;
                res = null;
                // 卸载操作
            }
        }
        void AsyncLoadEndCall(ResourceRequest req, UnityEngine.Object res)
        {
            req.res = res;
            if (null != req.res)
                req.m_state = RequestState.Loaded;
            else
                req.m_state = RequestState.Fail;
            if (null != loadEndCb)
            {
                loadEndCb(this);
            }
        }
    }

    public class ResourceObserver
    {
        public ResourceObserver(System.Action<bool, UnityEngine.Object> _cb)
        {
            m_cb = _cb;
        }
        public System.Action<bool, UnityEngine.Object> cb { get { return m_cb; } }
        System.Action<bool, UnityEngine.Object> m_cb;
        public uint id = 0;
        public ResourceState resState;

        public void ResetCb() { m_cb = null; }
        // 重置数据，一般不调用
        public void ResetAll() 
        {
            this.ResetCb();
            id = 0;
            resState = null;
        }
        // 释放自己，会检查是否卸载资源
        public void Release()
        {
            if (null != resState)
            {
                resState.RemoveObserver(id);
            }
        }
    }
    public class ResourceState
    {
        public ResourceState(ResourceLoader _loader)
        {
            loader = _loader;
        }

        public ResourceLoader loader;
        public ResourceRequest req;

        uint m_lastObserverId = 0;
        Dictionary<uint, ResourceObserver> m_observers = new Dictionary<uint, ResourceObserver>();
        public ResourceObserver AddObserver(System.Action<bool, UnityEngine.Object> cb)
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
        public int GetObserverCount()
        {
            return m_observers.Count;
        }
    }
}

