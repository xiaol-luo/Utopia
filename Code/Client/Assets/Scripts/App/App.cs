using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;

public class App 
{
    public static App my { get { return m_my; } }
    protected static App m_my = null;
    public static void GenInstance(MonoBehaviour _owner)
    {
        if (null == m_my)
            m_my = new App(_owner);
    }
    protected App(MonoBehaviour mono)
    {
        owner = mono;
        uiRoot = mono.transform.Find("UIRoot").transform;
    }
    public MonoBehaviour owner { get; protected set; }
    public Transform uiRoot { get; protected set; }
    public GameNetwork gameNetwork { get; protected set; }
    public GameConfig gameConfig { get; protected set; }
    public AppStateMgr stateMgr { get; protected set; }

    public void Awake()
    {
        stateMgr = new AppStateMgr();
        gameNetwork = new GameNetwork();
        gameConfig = new GameConfig();
        gameConfig.Awake();
    }
    public void Start ()
    {
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
