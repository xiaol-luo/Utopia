
using UnityEngine;

namespace Utopia
{
    class CoreMain : MonoBehaviour
    {
        void Awake()
        {
            DontDestroyOnLoad(gameObject);
            Core.MakeInstance(this);
            Core.instance.Awake();
        }

        void Start()
        {
            Core.instance.Start();
        }

        void Update()
        {
            Core.instance.Update();
        }

        void LateUpdate()
        {
            Core.instance.LateUpdate();
        }

        void FixedUpdate()
        {
            Core.instance.FixedUpdate();
        }

        void OnApplicationQuit()
        {
            Core.instance.Quit();
        }
    }
}
