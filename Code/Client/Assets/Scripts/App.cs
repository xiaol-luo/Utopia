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
            int ctx_len = sizeof(uint) + ping.CalculateSize();
            byte[] sendBuffer = new byte[ctx_len];

            int offset = 0;
            byte[] tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(1));
            Array.Copy(tmpBuffer, 0, sendBuffer, offset, tmpBuffer.Length);
            offset += tmpBuffer.Length;

            MemoryStream mms2 = new MemoryStream();
            CodedOutputStream output = new CodedOutputStream(mms2, true);
            ping.WriteTo(output);
            output.Flush();
            Array.Copy(mms2.GetBuffer(), 0, sendBuffer, offset, mms2.Position);
            offset += (int)mms2.Position;
            m_gameNetwork.Send(sendBuffer, 0, sendBuffer.Length);
        }
    }

    void FixedUpdate()
    {
        gameNetwork.UpdateIO();
    }
}
