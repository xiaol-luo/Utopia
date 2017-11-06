using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class ClientSocket 
{
    public enum State
    {
        Free = 0,
        Connecting,
        Connected,
        Error,
    }
    public class ThreadParam
    {
        public bool isExit = true; // main write
        public State state = State.Free; // main write
        public Mutex mtx = new Mutex();
        public Socket socket = null;
        public List<byte[]> recvBytes = null;
        public List<byte[]> sendBytes = null;
        public int errno = 0; 
        public string errmsg = string.Empty;
    }
    Thread m_thread;
    ThreadParam m_threadParam = new ThreadParam();
    List<byte[]>[] m_recvBytesArray = new List<byte[]>[2] { new List<byte[]>(), new List<byte[]>() };
    List<byte[]>[] m_sendBytesArray = new List<byte[]>[2] { new List<byte[]>(), new List<byte[]>() };
    public long id { get; set; }
    public string host { get; protected set; }
    public int port { get; protected set; }
    public State state { get { return m_threadParam.state; } }
    public int errno { get { return m_threadParam.errno; } }
    public string errmsg { get { return m_threadParam.errmsg; } }
    private System.Action m_asyncDoCnnCb;
    private System.Action<List<byte[]>> m_recvDataCb;
    private System.Action m_closeCb;

    public ClientSocket() : this(string.Empty, 0)
    {
    }
    public ClientSocket(string _host, int _port)
    {
        this.Reset(_host, _port);
    }
    public void Reset(string _host, int _port)
    {
        this.Close(State.Free);
        id = 0;
        host = _host;
        port = _port;
    }
    public void Close(State state=State.Free)
    {
        m_threadParam.isExit = true;
        if (null != m_thread)
        {
            m_thread.Join();
            m_thread = null;
        }

        if (null != m_closeCb)
            m_closeCb();
        m_closeCb = null;
        m_recvDataCb = null;
        m_tmpCnnCb = null;
        m_tmpSocket = null;
        m_asyncDoCnnCb = null;
        m_threadParam.state = state;
        if (null != m_threadParam.socket)
            m_threadParam.socket.Close();
        m_threadParam.socket = null;
        m_recvBytesArray[0].Clear();
        m_recvBytesArray[1].Clear();
        m_sendBytesArray[0].Clear();
        m_sendBytesArray[1].Clear();
        m_threadParam.errno = 0;
        m_threadParam.errmsg = string.Empty;
    }
    protected static void ConnectResult(IAsyncResult ar)
    {
        if (ar.IsCompleted)
        {
            object[] param = ar.AsyncState as object[];
            ClientSocket pThis = param[0] as ClientSocket;
            Socket socket = param[1] as Socket;
            

            if (pThis.m_tmpSocket != socket)
            {
                socket.Close();
                socket = null;
            }
            else
            {
                pThis.m_tmpSocket = null;
                pThis.m_threadParam.socket = socket;
                if (null != pThis.m_tmpCnnCb)
                {
                    bool isSucc = socket.Connected;
                    System.Action<bool> tmpCnnCb = pThis.m_tmpCnnCb;
                    pThis.m_asyncDoCnnCb = () => { tmpCnnCb(isSucc); };
                    pThis.m_tmpCnnCb = null;
                }
                if (socket.Connected)
                {
                    pThis.m_threadParam.state = State.Connected;
                    pThis.m_threadParam.recvBytes = pThis.m_recvBytesArray[0];
                    pThis.m_threadParam.sendBytes = pThis.m_sendBytesArray[0];
                    pThis.m_threadParam.isExit = false;
                    pThis.m_thread = new Thread(new ParameterizedThreadStart(ClientSocket.Loop));
                    pThis.m_thread.Start(pThis.m_threadParam);
                }
                else
                {
                    pThis.m_threadParam.state = State.Error;
                }
            }

            socket.EndConnect(ar);
        }
    }
    
    public bool Send(byte[] data, int offset, int data_len)
    {
        if (State.Connected == state && offset >= 0 && data_len > 0 && data.Length >= offset + data_len)
        {
            byte[] newBytes = new byte[data_len];
            Array.Copy(data, offset, newBytes, 0, data_len);
            List<byte[]> sendBytes = m_sendBytesArray[0];
            if (sendBytes == m_threadParam.sendBytes)
                sendBytes = m_sendBytesArray[1];
            sendBytes.Add(newBytes);
            return true;
        }
        return false;
    }

    Socket m_tmpSocket = null;
    System.Action<bool> m_tmpCnnCb = null;

    public bool ConnectAsync(System.Action<bool> cnnCb, System.Action<List<byte[]>> recvDataCb, System.Action closeCb)
    {
        if (State.Free != m_threadParam.state)
            return false;
        Socket socket = null;
        try
        {
            m_threadParam.state = State.Connecting;
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Blocking = true;
            socket.ReceiveTimeout = 1;
            socket.SendTimeout = 1;
            object[] param = new object[2];
            param[0] = this;
            param[1] = socket;
            socket.BeginConnect(host, port, ConnectResult, param);
        }
        catch (Exception)
        {
            m_threadParam.state = State.Free;
            socket = null;
        }
        if (null == socket)
        {
            if (null != cnnCb)
                cnnCb(false);
        }
        else
        {
            m_tmpSocket = socket;
            m_tmpCnnCb = cnnCb;
            m_closeCb = closeCb;
            m_recvDataCb = recvDataCb;
        }
        return null != socket;
    }
    public void UpdateIO()
    {
        if (null != this.m_asyncDoCnnCb)
        {
            System.Action asyncDoCnnCb = this.m_asyncDoCnnCb;
            this.m_asyncDoCnnCb = null;
            asyncDoCnnCb();
        }

        if (State.Connected != m_threadParam.state)
            return;
        if (0 != m_threadParam.errno)
        {
            this.Close(State.Error);
        }
        else
        {
            List<Byte[]> recvBytes = null;
            m_threadParam.mtx.WaitOne();
            recvBytes = m_threadParam.recvBytes;
            if (m_threadParam.recvBytes == m_recvBytesArray[0])
                m_threadParam.recvBytes = m_recvBytesArray[1];
            else
                m_threadParam.recvBytes = m_recvBytesArray[0];

            if (m_threadParam.sendBytes.Count <= 0)
            {
                if (m_threadParam.sendBytes == m_sendBytesArray[0])
                    m_threadParam.sendBytes = m_sendBytesArray[1];
                else
                    m_threadParam.sendBytes = m_sendBytesArray[0];
            }
            m_threadParam.mtx.ReleaseMutex();
            if (null != recvBytes && recvBytes.Count > 0)
            {
                try
                {
                    if (null != m_recvDataCb)
                        m_recvDataCb(recvBytes);
                }
                catch (Exception)
                {

                }
                recvBytes.Clear();
            }
        }
    }
    public static void Loop(object param)
    {
        byte[] recvBuffer = new byte[40960];
        List<byte[]> tmpSendBytes = new List<byte[]>();

        ThreadParam threadParam = param as ThreadParam;
        while (!threadParam.isExit && 0 == threadParam.errno && State.Connected == threadParam.state)
        {
            const int TIMEOUT_ERRNO = 10060;
            try
            {
                // receive
                int recvLen = threadParam.socket.Receive(recvBuffer, 0, recvBuffer.Length, SocketFlags.None);
                if (recvLen <= 0)
                {
                    threadParam.errno = 2;
                    threadParam.errmsg = "remote close socket";
                }
                else
                {
                    byte[] bytes = new byte[recvLen];
                    Array.Copy(recvBuffer, bytes, recvLen);
                    threadParam.mtx.WaitOne();
                    threadParam.recvBytes.Add(bytes);
                    threadParam.mtx.ReleaseMutex();
                }
            }
            catch (Exception e)
            {
                SocketException se = e as SocketException;
                if (null == se || TIMEOUT_ERRNO != se.ErrorCode)
                {
                    threadParam.errno = 1;
                    threadParam.errmsg = e.Message;
                    continue;
                }
            }
            try
            {
                // send
                threadParam.mtx.WaitOne();
                tmpSendBytes.AddRange(threadParam.sendBytes);
                threadParam.sendBytes.Clear();
                threadParam.mtx.ReleaseMutex();

                int i = 0;
                int lastSendLen = 0;
                for (; i < tmpSendBytes.Count; ++i)
                {
                    byte[] currBytes = tmpSendBytes[i];
                    lastSendLen = threadParam.socket.Send(currBytes);
                    if (lastSendLen < currBytes.Length)
                        break;
                }
                if (i >= tmpSendBytes.Count)
                {
                    tmpSendBytes.Clear();
                }
                else
                {
                    byte[] lastBytes = tmpSendBytes[i];
                    byte[] lastLeftBytes = new byte[lastBytes.Length - lastSendLen];
                    Array.Copy(lastBytes, lastSendLen, lastLeftBytes, 0, lastLeftBytes.Length);
                    if (i == tmpSendBytes.Count - 1)
                        tmpSendBytes.Clear();
                    else
                        tmpSendBytes = tmpSendBytes.GetRange(i + 1, tmpSendBytes.Count);
                    tmpSendBytes.Insert(0, lastLeftBytes);
                }
            }
            catch (Exception e)
            {
                SocketException se = e as SocketException;
                if (null == se || TIMEOUT_ERRNO != se.ErrorCode)
                {
                    threadParam.errno = 1;
                    threadParam.errmsg = e.Message;
                    continue;
                }
            }
        }
    }
}



