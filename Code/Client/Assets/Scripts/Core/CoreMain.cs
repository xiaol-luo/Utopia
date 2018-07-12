
using UnityEngine;

namespace Utopia
{
    class CoreMain : MonoBehaviour
    {
        void Start()
        {
            DontDestroyOnLoad(gameObject);
            Core.MakeInstance(this);
            Core.instance.Awake();
        }

        void FixedUpdate()
        {
            Core.instance.Update();
        }

        void OnApplicationQuit()
        {
            Core.instance.Release();
        }
    }
}
