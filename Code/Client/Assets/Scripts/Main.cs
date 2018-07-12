
using UnityEngine;

namespace Utopia
{
    class Main : MonoBehaviour
    {
        void Awake()
        {
            DontDestroyOnLoad(gameObject);
            App.MakeInstance(this);
            App.instance.Awake();
        }

        void Start()
        {
            App.instance.Start();
        }

        void FixedUpdate()
        {
            App.instance.FixedUpdate();
        }

        void OnApplicationQuit()
        {
            App.instance.Quit();
        }
    }
}