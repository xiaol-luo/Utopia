using System;
using System.Collections;
using System.Collections.Generic;

namespace Utopia
{
    public class ResourceObserver
    {
        public ResourceObserver(System.Action<string, ResourceObserver> _cb)
        {
            m_cb = _cb;
        }
        public System.Action<string, ResourceObserver> cb { get { return m_cb; } }
        System.Action<string, ResourceObserver> m_cb;
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
                this.ResetAll();
            }
        }

        public string path
        {
            get
            {
                var ret = (null != resState) ? resState.path : string.Empty;
                return ret;

            }
        }

        public UnityEngine.Object res
        {
            get
            {
                var ret = (null != resState) ? resState.res : null;
                return ret;
            }
        }

        public bool isValid
        {
            get
            {
                if (0 == id || null == resState)
                    return false;
                return resState.isValid;
            }
        }

        public bool isDone
        {
            get
            {
                var ret = (null != resState) ? resState.isDone : false;
                return ret;
            }
        }

        public bool isLoaded
        {
            get
            {
                var ret = (null != resState) ? resState.isLoaded : false;
                return ret;
            }
        }

        public bool isLoadFail
        {
            get
            {
                var ret = (null != resState) ? resState.isLoadFail : false;
                return ret;
            }
        }

        public bool isUnloaded
        {
            get
            {
                var ret = (null != resState) ? resState.isUnloaded : false;
                return ret;
            }
        }

        public void AddRef()
        {
            if (null != resState)
            {
                resState.AddRef();
            }
        }

        public void SubRef()
        {
            if (null != resState)
            {
                resState.SubRef();
            }
        }

        public int refCount
        {
            get
            {
                int ret = (null != resState) ? resState.refCount : 0;
                return ret;
            }
        }
        public T Instantiate<T>(UnityEngine.Vector3 position, UnityEngine.Quaternion rotation) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != resState)
                ret = resState.Instantiate<T>(position, rotation);
            return ret;
        }

        public T Instantiate<T>(UnityEngine.Transform parent, bool worldPositionStays) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != resState)
            {
                ret =  resState.Instantiate<T>(parent, worldPositionStays);
            }
            return ret;
        }
        public T Instantiate<T>(UnityEngine.Transform parent) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != resState)
            {
                ret = resState.Instantiate<T>(parent);
            }
            return ret;
        }
        public T Instantiate<T>(UnityEngine.Vector3 position, UnityEngine.Quaternion rotation, UnityEngine.Transform parent) where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != resState)
            {
                ret = resState.Instantiate<T>(position, rotation, parent);
            }
            return ret;
        }
        public T Instantiate<T>() where T : UnityEngine.Object
        {
            T ret = default(T);
            if (null != resState)
            {
                ret = resState.Instantiate<T>();
            }
            return ret;
        }
    }
}

