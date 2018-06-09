
using UnityEngine;

namespace Utopia
{
    class NewMain : MonoBehaviour
    {
        void Awake()
        {
            DontDestroyOnLoad(gameObject);
            NewApp.MakeInstance(this);
            NewApp.instance.Awake();
        }

        void Start()
        {
            NewApp.instance.Start();
        }

        void Update()
        {
            NewApp.instance.Update();
        }

        void LateUpdate()
        {
            NewApp.instance.LateUpdate();
        }

        void FixedUpdate()
        {
            NewApp.instance.FixedUpdate();
        }

        void OnApplicationQuit()
        {
            NewApp.instance.Quit();
        }
    }
}
