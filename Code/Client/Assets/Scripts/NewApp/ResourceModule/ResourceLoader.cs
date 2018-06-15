
using System;
using System.Collections.Generic;
using UnityEngine.SceneManagement;

namespace Utopia
{
    public class ResourceLoader
    {
        static ResourceLoader _instance = null;
        public static ResourceLoader instance
        {
            get
            {
                if (null == _instance)
                    _instance = new ResourceLoader();
                return _instance;
            }
        }
        protected ResourceLoader() {}

#if USE_AB
        IResourceLoaderImpl m_resLoader = new ResourceLoaderImplAB();
#else
        IResourceLoaderImpl m_resLoader = new ResourceLoaderImplEditor();
#endif
        Dictionary<string, ResourceState> m_resStates = new Dictionary<string, ResourceState>();
        ulong m_lastReqId = 0;
        ulong GenReqId()
        {
            ++m_lastReqId;
            if (m_lastReqId <= 0)
                m_lastReqId = 1;
            return m_lastReqId;
        }

        protected ResourceState GetResState(string path)
        {
            ResourceState ret = null;
            m_resStates.TryGetValue(path, out ret);
            return ret;
        }
        public UnityEngine.Object LoadAsset(string path)
        {
            UnityEngine.Object ret = null;
            ResourceState resState = this.GetResState(path);
            if (null != resState && null != resState.req && resState.req.isLoaded)
            {
                ret = resState.req.res;
            }
            else
            {
                ret = m_resLoader.Load(path);
            }
            return ret;
        }
        public ResourceObserver AsyncLoadAsset(string path, System.Action<string, UnityEngine.Object> cb)
        {
            ResourceState resState = this.GetResState(path);
            if (null == resState)
            {
                resState = new ResourceState(this);
                ulong reqId = this.GenReqId();
                resState.req = ResourceRequest.CreateAsyncRequest(m_resLoader, path, this.ResLoadEndCall, reqId);
                m_resStates.Add(path, resState);
                resState.req.AsyncLoad();
            }
            else
            {
                // Ä£ÄâÒì²½
                NewApp.instance.timerModule.Add(() => { this.ResLoadEndCall(resState.req); }, 0); 
            }
            ResourceObserver ret = resState.AddObserver(cb);
            return ret;
        }
        public ResourceObserver CoLoadAsset(string path)
        {
            ResourceState resState = this.GetResState(path);
            if (null == resState)
            {
                resState = new ResourceState(this);
                ulong reqId = this.GenReqId();
                resState.req = ResourceRequest.CreateAsyncRequest(m_resLoader, path, this.ResLoadEndCall,reqId);
                m_resStates.Add(path, resState);
                resState.req.AsyncLoad();
            }
            ResourceObserver ret = resState.AddObserver(null);
            return ret;
        }

        public void RemoveResObserver(ResourceObserver ob)
        {
            if (null != ob && null != ob.resState)
            {
                ob.resState.RemoveObserver(ob.id);
            }
        }

        public void CheckUnloadRes(string path, ulong id)
        {
            ResourceState resState = this.GetResState(path);
            if (null != resState && 
                null != resState.req &&
                resState.req.id == id && 
                resState.req.isDone &&
                resState.observerCount <= 0)
            {
                m_resStates.Remove(path);
                resState.req.UnloadRes();
            }
        }

        public void ResLoadEndCall(ResourceRequest req)
        {
            ResourceState resState = this.GetResState(req.path);
            if (null != resState && null != resState.req && req.id == resState.req.id)
            {
                foreach (ResourceObserver ob in resState.GetObservers())
                {
                    if (null != ob.cb)
                    {
                        ob.cb(req.path, req.res);
                        ob.ResetCb();
                    }
                }
                if (!req.isLoaded)
                {
                    m_resStates.Remove(req.path);
                }
                else
                {
                    this.CheckUnloadRes(req.path, req.id);
                }
            }
        }
    }
}