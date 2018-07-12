using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace Utopia.Resource
{
    class GameObjectRefMonitorMono : MonoBehaviour
    {
        ResourceState resState;

        public static void Add(GameObject go, ResourceState resState)
        {
            var cmp = go.AddComponent<GameObjectRefMonitorMono>();
            cmp.resState = resState;
            cmp.resState.AddRef();
        }
        private void OnDestroy()
        {
            resState.SubRef();
        }
    }
}