
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
            InvokeRepeating("Tick", 0.0f, 0.01f);
        }
        void Tick()
        {
            App.instance.FixedUpdate();
        }

        void OnApplicationQuit()
        {
            App.instance.Quit();
        }
    }
}