using System;
using System.Collections;
using System.Collections.Generic;

namespace Utopia
{
    public class ResourceObserver
    {
        public ResourceObserver(System.Action<string, UnityEngine.Object> _cb)
        {
            m_cb = _cb;
        }
        public System.Action<string, UnityEngine.Object> cb { get { return m_cb; } }
        System.Action<string, UnityEngine.Object> m_cb;
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
    }
}

