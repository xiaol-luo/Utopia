using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System;
using Google.Protobuf;

public class TryNetwork : MonoBehaviour {

    public string host = "127.0.0.1";
    public int port = 10240;

    Socket socket = null;

    Ping ping;

    ClientSocket client_socket;

    void Start ()
    {
        host = "192.168.5.103";
        port = 10240;
        ping = new Ping();
        ping.Userid = 1;
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (null != client_socket)
        {
            client_socket.UpdateIO();
        }

        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            if (null == client_socket)
            {
                client_socket = new ClientSocket(host, port);
                client_socket.ConnectAsync(null);
            }
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            if (null != client_socket)
            {
                int ctx_len = (sizeof(int) + ping.CalculateSize());
                byte[] sendBuffer = new byte[ctx_len + sizeof(uint)];
                byte[] tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(ctx_len));
                int offset = 0;
                Array.Copy(tmpBuffer, 0, sendBuffer, offset, tmpBuffer.Length);
                offset += tmpBuffer.Length;

                tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(1));
                Array.Copy(tmpBuffer, 0, sendBuffer, offset, tmpBuffer.Length);
                offset += tmpBuffer.Length;

                MemoryStream mms2 = new MemoryStream();
                CodedOutputStream output = new CodedOutputStream(mms2, true);
                ping.WriteTo(output);
                output.Flush();

                Array.Copy(mms2.GetBuffer(), 0, sendBuffer, offset, mms2.Position);
                offset += (int)mms2.Position;

                client_socket.Send(sendBuffer, 0, sendBuffer.Length);
            }
        }
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            if (null != client_socket)
            {
                client_socket.Close();
                client_socket = null;
            }
        }
    }
}
