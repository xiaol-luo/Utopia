

using Google.Protobuf;
using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using UnityEngine;

public class NetAgent
{
    INetAgentHandler m_handler;
    public void SetHandler(INetAgentHandler handler) { m_handler = handler; }

    public string host { get; protected set; }
    public int port { get; protected set; }
    public ClientSocket socket { get; protected set; }
    public ulong id { get; set; }

    public bool Connect(string _host , int _port)
    {
        this.Close();
        host = _host;
        port = _port;
        socket = new ClientSocket(host, port);
        return socket.ConnectAsync(OnSocketOpen, OnSocketRecvData, OnSocketClose);
    }
    public bool ReConnect()
    {
        return this.Connect(host, port);
    }
    public void Close()
    {
        if (null != socket)
            socket.Close();
        socket = null;
        m_parseBufferOffset = 0;
    }
    public void UpdateIO()
    {
        if (null != socket)
            socket.UpdateIO();
    }
    public bool Send(byte[] data, int offset, int len)
    {
        if (null != socket && 0 == socket.errno && 
            null != data && offset >= 0 && len > 0 && offset + len <= data.Length)
        {
            return socket.Send(data, offset, len);

        }
        return false;
    }
    public bool Send(int protocolId, IMessage msg)
    {
        if (protocolId <= 0 || null == msg)
            return false;

        bool isOk = true;
        if (isOk)
        {
            int ctxLen = sizeof(int) + msg.CalculateSize();
            byte[] tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(ctxLen));
            isOk = this.Send(tmpBuffer, 0, tmpBuffer.Length);
        }
        if(isOk)
        {
            byte[] tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(protocolId));
            isOk = this.Send(tmpBuffer, 0, tmpBuffer.Length);
        }
        if (isOk)
        {
            MemoryStream mstream = new MemoryStream();
            CodedOutputStream cops = new CodedOutputStream(mstream, false);
            msg.WriteTo(cops);
            cops.Flush();
            isOk = this.Send(mstream.GetBuffer(), 0, (int)mstream.Position);
        }
        return isOk;
    }

    public bool Send(int protocolId)
    {
        if (protocolId <= 0)
            return false;

        bool isOk = true;
        if (isOk)
        {
            int ctxLen = sizeof(int);
            byte[] tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(ctxLen));
            isOk = this.Send(tmpBuffer, 0, tmpBuffer.Length);
        }
        if (isOk)
        {
            byte[] tmpBuffer = BitConverter.GetBytes(IPAddress.HostToNetworkOrder(protocolId));
            isOk = this.Send(tmpBuffer, 0, tmpBuffer.Length);
        }
        return isOk;
    }

    void OnSocketOpen(bool isSucc)
    {
        if (null != m_handler)
            m_handler.OnOpen(isSucc);
        if (!isSucc)
            this.Close();

        Debug.Log("OnSocketOpen ");
    }

    const int CONTENT_LEN_DESCRIPT_SIZE = sizeof(uint);
    const int PROTOCOL_LEN_DESCRIPT_SIZE = sizeof(int);
    const int PROTOCOL_CONTENT_MAX_SIZE = 409600;
    const int PROTOCOL_MAX_SIZE = PROTOCOL_LEN_DESCRIPT_SIZE + PROTOCOL_CONTENT_MAX_SIZE;
    byte[] m_parseBuffer = new byte[PROTOCOL_MAX_SIZE + CONTENT_LEN_DESCRIPT_SIZE];
    int m_parseBufferOffset = 0;
    void OnSocketRecvData(List<byte[]> bytesList)
    {
        foreach (byte[] bytes in bytesList)
        {
            int bytesOffset = 0;
            while (bytesOffset < bytes.Length)
            {
                if (m_parseBufferOffset < CONTENT_LEN_DESCRIPT_SIZE)
                {
                    int copyLen = CONTENT_LEN_DESCRIPT_SIZE - m_parseBufferOffset;
                    if (copyLen > bytes.Length - bytesOffset)
                        copyLen = bytes.Length - bytesOffset;
                    Array.Copy(bytes, bytesOffset, m_parseBuffer, m_parseBufferOffset, copyLen);
                    bytesOffset += copyLen;
                    m_parseBufferOffset += copyLen;
                    if (bytesOffset >= bytes.Length)
                        break;
                }
                int ctxLen = IPAddress.NetworkToHostOrder(BitConverter.ToInt32(m_parseBuffer, 0));
                if (ctxLen > PROTOCOL_MAX_SIZE || ctxLen < PROTOCOL_LEN_DESCRIPT_SIZE)
                {
                    Debug.Log("OnSocketRecvData ctxLen " + ctxLen.ToString());
                    this.Close();
                    return;
                }
                {
                    int copyLen = CONTENT_LEN_DESCRIPT_SIZE + ctxLen - m_parseBufferOffset;
                    if (copyLen > bytes.Length - bytesOffset)
                        copyLen = bytes.Length - bytesOffset;
                    Array.Copy(bytes, bytesOffset, m_parseBuffer, m_parseBufferOffset, copyLen);
                    bytesOffset += copyLen;
                    m_parseBufferOffset += copyLen;
                    if (m_parseBufferOffset >= CONTENT_LEN_DESCRIPT_SIZE + ctxLen)
                    {
                        int parseBufferOffset = m_parseBufferOffset;
                        m_parseBufferOffset = 0;

                        int protocolId = IPAddress.NetworkToHostOrder(BitConverter.ToInt32(m_parseBuffer, CONTENT_LEN_DESCRIPT_SIZE));
                        int protobufBegin = CONTENT_LEN_DESCRIPT_SIZE + PROTOCOL_LEN_DESCRIPT_SIZE;
                        if (null != m_handler)
                        {
                            try { m_handler.OnRecvData(protocolId, m_parseBuffer, protobufBegin, parseBufferOffset - protobufBegin); }
                            catch (Exception) {}
                        }
                    }
                }
            }
        }
    }

    void OnSocketClose()
    {
        if (null != m_handler)
            m_handler.OnClose(socket.errno, socket.errmsg);
        socket = null;
        this.Close();

        Debug.Log("OnSocketClose ");
    }
}