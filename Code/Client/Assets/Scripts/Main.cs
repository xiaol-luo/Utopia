
using UnityEngine;

class Main : MonoBehaviour
{
    void Awake()
    {

        DontDestroyOnLoad(gameObject);
        App.GenInstance(this);
        App.my.Awake();
    }

    void Start()
    {
        App.my.Start();
    }

    void Update()
    {
        App.my.Update();
    }

    void LateUpdate()
    {
        App.my.LateUpdate();
    }

    void FixedUpdate()
    {
        App.my.FixedUpdate();
    }

    void OnApplicationQuit()
    {
        App.my.Quit();
    }
}