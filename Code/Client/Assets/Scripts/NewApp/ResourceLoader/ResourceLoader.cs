
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
        public ResourceState GetLoadedResState(string path)
        {
            ResourceState resState = this.GetResState(path);
            if (null == resState || !resState.isLoaded)
                return null;
            return resState;
        }
        public ResourceObserver LoadAsset(string path)
        {
            ResourceObserver retOb = null;
            ResourceState resState = this.GetResState(path);
            /*
             * resState.req.isLoaded will be loading or isLoaded.
             * if it fail, it will be remove by funciton ResLoadEndCall
             */
            if (null != resState && null != resState.req && resState.req.isLoaded) 
            {
                retOb = resState.AddObserver(null);
            }
            else
            {
                UnityEngine.Object ret = m_resLoader.Load(path);
                if (null != ret)
                {
                    if (null == resState)
                    {
                        resState = new ResourceState(this);
                        ulong reqId = this.GenReqId();
                        resState.req = ResourceRequest.CreateRequest(m_resLoader, path, ret, reqId);
                        m_resStates.Add(path, resState);
                        retOb = resState.AddObserver(null);
                    }
                    else
                    {
                        retOb = resState.AddObserver(null);
                        resState.req.SetRes(ret);
                    }
                }
            }
            return retOb;
        }
        public ResourceObserver AsyncLoadAsset(string path, System.Action<string, ResourceObserver> cb)
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
                // ģ���첽
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
                resState.observerCount <= 0
                && resState.refCount <= 0)
            {
                m_resStates.Remove(path);
                resState.req.UnloadRes();
                resState.req = null;
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
                        ob.cb(req.path, ob);
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