using UnityEngine;
using UnityEditor;
using UnityEngine.EventSystems;

namespace Utopia
{


    public class ScenePlane : MonoBehaviour, IPointerDownHandler
    {
        
        private void Start()
        {
            
        }
        public void OnPointerDown(PointerEventData eventData)
        {
            Core.instance.log.LogDebug("ScenePlane OnPointerDown {0} {1} {2}",
                eventData.pointerCurrentRaycast.worldPosition.x, 
                eventData.pointerCurrentRaycast.worldPosition.y,
                eventData.pointerCurrentRaycast.worldPosition.z);

            Core.instance.eventMgr.Fire(SceneEventDef.MouseHitGround, eventData);
        }
    }
}