
using System.Collections;
using UnityEngine;
using UnityEngine.UI;

namespace Utopia.Resource
{
    class ImageRefMonitorMono : ResourceRefMonitorMono<Image, Sprite>
    {
        public static void Set(Image image, string assetPath, System.Action<Image, Sprite> onEnd)
        {
            Set<ImageRefMonitorMono>(image, assetPath, onEnd);
        }
        public static void Set(Image image, string assetPath, bool isSetSize = false)
        {
            Set<ImageRefMonitorMono>(image, assetPath, (i, s) => 
            {
                i.sprite = s;
                if (isSetSize)
                    i.SetNativeSize();
            });
        }
        public static IEnumerator CoSet(Image image, string assetPath, bool isSetSize = false)
        {
            bool isDone = false;
            Set<ImageRefMonitorMono>(image, assetPath, (i, s) =>
            {
                isDone = true;
                i.sprite = s;
                if (isSetSize)
                    i.SetNativeSize();
            });
            yield return new WaitUntil(() => { return isDone; });
        }
    }
}