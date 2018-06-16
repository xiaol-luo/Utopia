
using System;
using System.Collections.Generic;
using UnityEngine.SceneManagement;

namespace Utopia
{
    public class ResourceLoaderProxy
    {

        public static ResourceLoaderProxy Create()
        {
            return new ResourceLoaderProxy(ResourceLoader.instance);
        }

        ResourceLoader m_loader;
        public ResourceLoaderProxy(ResourceLoader _loader)
        {
            m_loader = _loader;
        }

        Dictionary<string, ResourceObserver> m_resObservers = new Dictionary<string, ResourceObserver>();

        protected ResourceObserver GetResObserver(string path)
        {
            ResourceObserver ret = null;
            m_resObservers.TryGetValue(path, out ret);
            if (null != ret && !ret.isValid)
            {
                m_resObservers.Remove(path);
                ret = null;
            }
            return ret;
        }
        public ResourceObserver GetLoadedResState(string path)
        {
            ResourceObserver resState = this.GetResObserver(path);
            if (null == resState || !resState.isLoaded)
                return null;
            return resState;
        }
        public ResourceObserver LoadAsset(string path)
        {
            ResourceObserver ret = this.GetLoadedResState(path);
            if (null == ret)
            {
                ret = m_loader.LoadAsset(path);
                if (null != ret && ret.isValid && null == GetResObserver(path))
                {
                    m_resObservers.Add(ret.path, ret);
                }
                else
                {
                    ret.Release();
                    ret = this.GetLoadedResState(path);
                }
            }
            return ret;
        }
        public ResourceObserver AsyncLoadAsset(string path, System.Action<string, ResourceObserver> cb)
        {
            ResourceObserver ret = this.GetLoadedResState(path);
            if (null == ret)
            {
                ret = m_loader.AsyncLoadAsset(path, (string resPath, ResourceObserver resOb) => {
                    if (null == this.GetResObserver(path) && null != ret && ret.isValid)
                    {
                        m_resObservers.Add(ret.path, ret);
                    }
                    else
                    {
                        ret.Release();
                    }
                    if (null != cb)
                    {
                        cb(resPath, resOb);
                    }
                });
            }
            else
            {
                if (null != cb)
                {
                    NewApp.instance.timerModule.Add(() => {
                        cb(path, ret);
                    }, 0);
                }
            }
            return ret;
        }
        public ResourceObserver CoLoadAsset(string path)
        {
            ResourceObserver ret = this.GetResObserver(path);
            if (null == ret)
            {
                ret = m_loader.CoLoadAsset(path);
                m_resObservers.Add(ret.path, ret);

            }
            return ret;
        }
        public void UnloadAsset(string path)
        {
            var ob = this.GetResObserver(path);
            if (null != ob && ob.isValid)
            {
                m_resObservers.Remove(path);
                ob.Release();
            }
        }

        public void Release()
        {
            foreach (ResourceObserver ob in m_resObservers.Values)
            {
                ob.Release();
            }
            m_resObservers.Clear();
        }
    }
}