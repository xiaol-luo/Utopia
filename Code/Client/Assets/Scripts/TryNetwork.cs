using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System;
using Google.Protobuf;

public class TryNetwork : MonoBehaviour, NetAgentHandler {

    public string host = "127.0.0.1";
    public int port = 10240;

    Socket socket = null;

    Ping ping;

    ClientSocket client_socket;
    NetAgent netAgent = new NetAgent();
    ProtocolHandler protocolHandler = new ProtocolHandler();

    public void OnClose(int errno, string errMsg)
    {

    }

    public void OnOPen(bool isSucc)
    {
    }

    public void OnRecvData(int protocolId, byte[] data, int dataBegin, int dataLen)
    {
        protocolHandler.OnMessage(protocolId, data, dataBegin, dataLen);
    }

    void Start ()
    {
        // host = "192.168.5.103";
        port = 10240;
        ping = new Ping();
        ping.Userid = 1;

        netAgent.SetHandler(this);
        protocolHandler.Add<Ping>(1, (int id, Ping msg)=> 
        {
            Debug.Log("Ping " + msg.ToString());
        });

        protocolHandler.Add<Pong>(2, (int id, Pong msg) =>
        {
            Debug.Log("Pong " + msg.ToString());
        });
    }
	
	// Update is called once per frame
	void Update ()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            netAgent.Connect(host, port);
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
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

            netAgent.Send(sendBuffer, 0, sendBuffer.Length);
        }
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            netAgent.Close();
        }
    }

    void FixedUpdate()
    {
        netAgent.UpdateIO();
    }
}
