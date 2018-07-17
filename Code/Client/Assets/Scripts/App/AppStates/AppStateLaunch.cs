
using UnityEngine;
using Utopia;

public class AppStateLaunch : AppStateBase
{
    public AppStateLaunch(IStateMgr stateMgr) : base(stateMgr, (int)AppStateBase.StateName.Launch)
    {

    }

    UIConnectServer m_mono = null;
    string m_lastUsedIp = "127.0.0.1";
    string m_lastUsedPort = "10240";

    public override void Enter(params object[] objs)
    {
        m_mono = App.instance.uiRoot.GetComponentInChildren<UIConnectServer>();
        if (null == m_mono)
        {
            Object prefab = Resources.Load("Art/UI/Prefabs/UIConnectServer");
            GameObject go = GameObject.Instantiate(prefab) as GameObject;
            m_mono = go.GetComponent<UIConnectServer>();
            m_mono.transform.SetParent(App.instance.uiRoot);
            m_mono.transform.localPosition = Vector3.zero;
            m_mono.transform.localScale = Vector3.one;
        }
        m_mono.ip = m_lastUsedIp;
        m_mono.port = m_lastUsedPort;
        App.instance.gameNetwork.openCb += this.OnConnected;
        App.instance.gameNetwork.closeCb += this.OnDisConnect;
    }

    public override void Exit(params object[] objs)
    {
        if (null != m_mono)
        {
            m_lastUsedIp = m_mono.ip;
            m_lastUsedPort = m_mono.port;
            GameObject.Destroy(m_mono.gameObject);
        }
            
        m_mono = null;
        App.instance.gameNetwork.openCb -= this.OnConnected;
        App.instance.gameNetwork.closeCb -= this.OnDisConnect;
    }

    public override void Update(params object[] objs)
    {

    }

    void OnConnected(bool isSucc)
    {
        if (!isSucc)
        {
            if (null != m_mono)
            {
                m_mono.errMsg = "AppStateLaunch OnConnected Fail!";
            }
        }
        else
        {
            // Ping ping = new Ping();
            // App.my.gameNetwork.Send((int)ProtoId.PidPing, ping);
        }

        m_stateMgr.ChangeState(AppStateBase.StateName.SelectHero);
    }
    void OnDisConnect(int errno, string errMsg)
    {
        if (0 != errno)
        {
            if (null != m_mono)
            {
                m_mono.errMsg = string.Format("AppStateLaunch OnDisConnect {0} {1}", errno, errMsg);
            }
        }
    }
}