using UnityEngine;
using UnityEditor;
using Utopia.Net;

public class NetMgr 
{
    public GameSrvNetProxy gameSrv { get; protected set; }

    public void Init()
    {
        {
            gameSrv = new GameSrvNetProxy();
            GameSrvNetAgentHandler nah = new GameSrvNetAgentHandler();
            nah.SetNetProxy(gameSrv);
            nah.Init();
            gameSrv.SetNetAgentHandler(nah);
        }
    }
}