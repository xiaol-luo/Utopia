using UnityEngine;
using System.Collections;

namespace Utopia.Resource
{
    class AnimatorRATRefMonitorMono : ResourceRefMonitorMono<Animator, RuntimeAnimatorController>

    {
        public static void Set(Animator animator, string assetPath)
        {
            Set<AnimatorRATRefMonitorMono>(animator, assetPath, (i, s) => { animator.runtimeAnimatorController = s; });
        }

        public static void Set(Animator animator, string assetPath, System.Action<Animator, RuntimeAnimatorController> onEnd)
        {
            Set<AnimatorRATRefMonitorMono>(animator, assetPath, onEnd);
        }

        public static IEnumerator CoSet(Animator animator, string assetPath, System.Action<Animator, RuntimeAnimatorController> onEnd)
        {
            bool isDone = false;
            Set<AnimatorRATRefMonitorMono>(animator, assetPath, (a, r)=> 
            {
                isDone = true;
                onEnd(a, r);
            });
            yield return new WaitUntil(() => { return isDone; });
        }
    }
}