using System.Collections.Generic;
using UnityEngine;
using Utopia;

namespace Utopia.Resource
{
    class ResourceRefMonitorMono : MonoBehaviour
    {
        protected ResourceState resState;
        
        private void OnDestroy()
        {
            SetResourceState(null);
        }

        public void SetResourceState(ResourceState newResState)
        {
            if (null != newResState)
            {
                newResState.AddRef();
            }
            if (null != resState)
            {
                resState.SubRef();
            }
            resState = newResState;
        }
    }
    class ResourceRefMonitorMono<T, R> : ResourceRefMonitorMono where T : Component where R : Object
    {
        protected static void Set<RT>(T component, string assetPath, System.Action<T, R> onEnd) where RT : ResourceRefMonitorMono<T, R>
        {
            if (string.IsNullOrEmpty(assetPath))
            {
                var ai = component.GetComponent<RT>();
                if (ai != null)
                {
                    ai.SetResourceState(null);
                }
                onEnd(component, null);
            }
            else
            {
                RT ai = component.GetComponent<RT>();
                if (ai == null)
                    ai = component.gameObject.AddComponent<RT>();
                {
                    ResourceLoader.instance.AsyncLoadAsset(assetPath, (string ap, ResourceObserver ob) =>
                    {
                        if (null != ob && ob.isLoaded && null != ob.res && ob.res is R)
                        {
                            ai.SetResourceState(ob.resState);
                            onEnd(component, ob.res as R);
                        }
                        else
                        {
                            ai.SetResourceState(null);
                        }
                        ob.Release();
                    });
                }
            }
        }
    }
}