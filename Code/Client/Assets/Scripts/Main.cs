
using UnityEngine;

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

    void Update()
    {
        App.instance.Update();
    }

    void LateUpdate()
    {
        App.instance.LateUpdate();
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