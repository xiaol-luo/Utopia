using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;

public class TryNetwork : MonoBehaviour {

    public string host = "127.0.0.1";
    public int port = 10240;

    Socket socket = null;

	void Start ()
    {
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            if (null != socket)
                socket.Close();
            IPAddress ip = IPAddress.Parse(host);
            IPEndPoint ipe = new IPEndPoint(ip, port);
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Connect(ipe);
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            if (null != socket)
                socket.Close();
        }
    }
}
