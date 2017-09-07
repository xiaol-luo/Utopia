using Google.Protobuf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;

public class App : MonoBehaviour
{
    [SerializeField]
    string host = "192.168.5.105";
    [SerializeField]
    int port = 10240;
    string oldHost = string.Empty;
    int oldPort = 0;
    void CheckCnnInfoChange()
    {
        if (oldHost != host || oldPort != port)
        {
            m_gameNetwork.Connect(host, port);
            oldHost = host;
            oldPort = port;
        }
    }

    GameNetwork m_gameNetwork = new GameNetwork();
    public GameNetwork gameNetwork { get { return m_gameNetwork; } }

    private void Awake()
    {

    }
    void Start ()
    {
        gameNetwork.Add(1, (int id, Ping msg) =>
        {
            Debug.Log("ping " + msg.ToString());
        });
        gameNetwork.Add(2, (int id, Pong msg) =>
        {
            Debug.Log("pong " + msg.ToString());
        });
    }

	void Update ()
    {
        this.CheckCnnInfoChange();

        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            m_gameNetwork.ReConnect();
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            Ping ping = new Ping();
            ping.Userid = 1;
            gameNetwork.Send(1, ping);
        }
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            Config.CsvConfigSets cfgSets = new Config.CsvConfigSets();
            cfgSets.Load(Path.Combine(Application.dataPath, "Resources/Config/AutoCsvConfig"));
        }
    }

    void FixedUpdate()
    {
        gameNetwork.UpdateIO();
    }
}
