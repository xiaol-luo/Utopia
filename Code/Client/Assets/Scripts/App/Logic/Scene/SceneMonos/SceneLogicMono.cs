using UnityEngine;
using UnityEditor;
using UnityEngine.EventSystems;

namespace Utopia
{
    public class SceneLogicMono : MonoBehaviour
    {
        
        private void Start()
        {
            
        }

        private void Update()
        {

            if (EAppState.InBattle != App.instance.stateMgr.activeId)
                return;

            App.instance.scene.Update();
        }
    }
}