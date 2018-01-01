
using UnityEngine;

class Main : MonoBehaviour
{
    void Awake()
    {
        DontDestroyOnLoad(gameObject);
        App.GenInstance(this);
        App.my.Awake();

        Vector2 v1 = new Vector2(0, 1);
        Vector2 v2 = new Vector2(1, 0);
        Vector2 v3 = new Vector2(-1, 0);
        Vector2 v4 = new Vector2(0, -1);
        float ret = Vector2.SignedAngle(v1, v2);
        ret = Vector2.SignedAngle(v1, v3);
        ret = Vector2.SignedAngle(v1, v4);
        ret = Vector2.SignedAngle(v1, v1);

        float zz = Vector3.Angle(new Vector3(0, 0, 1), new Vector3(1, 0, 0));
        zz = Vector3.SignedAngle(new Vector3(0, 0, 1), new Vector3(1, 0, 0), new Vector3(0, 1, 0));
        zz = Vector3.SignedAngle(new Vector3(0, 0, 1), new Vector3(-1, 0, 0), new Vector3(0, 1, 0));
        ret = 0;
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