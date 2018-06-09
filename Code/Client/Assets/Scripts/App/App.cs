using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;

public class App 
{
    public static App instance { get { return m_instance; } }
    protected static App m_instance = null;
    public static void MakeInstance(MonoBehaviour _owner)
    {
        if (null == m_instance)
            m_instance = new App(_owner);
        else
            Debug.LogError("App is single instance, can only make one instance");
    }
    protected App(MonoBehaviour _mono)
    {
        root = _mono;
        uiRoot = root.transform.Find("UIRoot").transform;
    }
    public MonoBehaviour root { get; protected set; }
    public Transform uiRoot { get; protected set; }
    public GameNetwork gameNetwork { get; protected set; }
    public GameConfig gameConfig { get; protected set; }
    public AppStateMgr stateMgr { get; protected set; }
    public Scene scene { get; protected set; }
    public ulong heroId { get; set; }

    public void Awake()
    {
        stateMgr = new AppStateMgr();
        gameNetwork = new GameNetwork();
        gameConfig = new GameConfig();
        scene = new Scene();
        gameConfig.Awake();
    }
    public void Start ()
    {
        LayerUtil.Init();

        do
        {
            if (!gameConfig.Start())
            {
                Debug.LogError(string.Format("errno :{0}, error msg :{1}", gameConfig.errno, gameConfig.errMsg));
                break;
            }
        } while (false);

        stateMgr.ChangeState(IAppState.StateName.Launch);
    }

	public void Update ()
    {
        stateMgr.UpdateState();

        if (Input.GetKeyDown(KeyCode.Alpha3))
        {

        }
    }

    public void LateUpdate()
    {

    }

    public void FixedUpdate()
    {
        gameNetwork.UpdateIO();
    }

    public void Quit()
    {
        gameNetwork.Close();
    }
}
