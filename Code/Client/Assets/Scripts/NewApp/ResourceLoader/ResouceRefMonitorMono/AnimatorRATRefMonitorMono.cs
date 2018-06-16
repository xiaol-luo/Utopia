using UnityEngine;
using System.Collections;

namespace Utopia.Resource
{
    class AnimatorRATRefMonitorMono : ResourceRefMonitorMono<Animator, RuntimeAnimatorController>

    {
        public static void Set(Animator animator, string assetPath)
        {
            Set(animator, assetPath, (a, s) => {
                a.runtimeAnimatorController = s;
            });
        }

        public static void Set(Animator animator, string assetPath, System.Action<Animator, RuntimeAnimatorController> onEnd)
        {
            Set<AnimatorRATRefMonitorMono>(animator, assetPath, onEnd);
        }

        public static IEnumerator CoSet(Animator animator, string assetPath)
        {
            bool isDone = false;
            Set<AnimatorRATRefMonitorMono>(animator, assetPath, (a, r)=> 
            {
                isDone = true;
                a.runtimeAnimatorController = r;
            });
            yield return new WaitUntil(() => { return isDone; });
        }
    }
}