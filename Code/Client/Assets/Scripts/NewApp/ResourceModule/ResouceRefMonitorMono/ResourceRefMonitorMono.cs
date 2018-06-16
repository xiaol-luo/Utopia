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
            if (null != resState)
            {
                resState.SubRef();
                resState = null;
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
                {
                    ai = component.gameObject.AddComponent<RT>();
                }
                {
                    ResourceObserver ob = null;
                    ob = ResourceLoader.instance.AsyncLoadAsset(assetPath, (string ap, UnityEngine.Object o) =>
                    {
                        if (ob.isLoaded && null != o)
                        {
                            if (o is R)
                            {
                                ob.AddRef();
                                ai.SetResourceState(ob.resState);
                                onEnd(component, o as R);
                            }
                        }
                        ob.Release();
                    });
                }
            }
        }
    }
}