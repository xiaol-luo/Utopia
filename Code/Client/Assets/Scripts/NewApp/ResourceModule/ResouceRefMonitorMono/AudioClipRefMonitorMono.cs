using UnityEngine;
using UnityEngine.UI;
using System.Collections;

namespace Utopia.Resource
{
    class AudioClipRefMonitorMono : ResourceRefMonitorMono<AudioSource, AudioClip>
    {
        public static void Set(AudioSource image, string assetPath, System.Action<AudioSource, AudioClip> onEnd)
        {
            Set<AudioClipRefMonitorMono>(image, assetPath, onEnd);
        }

        public static void Set(AudioSource image, string assetPath)
        {
            Set<AudioClipRefMonitorMono>(image, assetPath, (i, s) => 
            {
                i.clip = s;
            });
        }

        public static IEnumerator CoSet(AudioSource image, string assetPath)
        {
            bool isDone = false;
            Set<AudioClipRefMonitorMono>(image, assetPath, (i, s) =>
            {
                isDone = true;
                i.clip = s;
            });
            yield return new WaitUntil(() => { return isDone; });
        }
    }
}