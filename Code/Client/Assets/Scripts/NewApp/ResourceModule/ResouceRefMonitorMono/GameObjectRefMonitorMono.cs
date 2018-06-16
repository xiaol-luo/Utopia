using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace Utopia.Resource
{
    class GameObjectRefMonitorMono : MonoBehaviour
    {
        ResourceState resState;

        public static void Add(GameObject go, ResourceState request)
        {
            request.AddRef();
            var cmp = go.AddComponent<GameObjectRefMonitorMono>();
            cmp.resState = request;
        }
        private void OnDestroy()
        {
            resState.SubRef();
        }
    }
}