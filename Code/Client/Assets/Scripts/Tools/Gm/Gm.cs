using UnityEngine;
using UnityEditor;
using UnityEngine.UI;
using Utopia;
using Utopia.Logic;
using NetProto;

public class Gm : MonoBehaviour
{
    bool m_isPanelShowed = false;

    private void OnGUI()
    {
        EditorGUILayout.BeginHorizontal();
        if (GUILayout.Button("退出"))
        {
            App.instance.logicMgr.GetModule<SelectHero>().SelectSide(SelectHero.SelectedSide.None);
            App.instance.stateMgr.ChangeState(EAppState.InLogic);
        }
        if (GUILayout.Button("断线"))
        {
            App.instance.net.gameSrv.Close();
        }
        if (GUILayout.Button("重新创建场景"))
        {
            RecreateSceneReq req = new RecreateSceneReq();
            req.SceneName = "TestScene";
            App.instance.net.gameSrv.Send(NetProto.PID.RecreateSceneReq, req);
        }
        if (GUILayout.Button("重载配置"))
        {
            App.instance.net.gameSrv.Send(NetProto.PID.ReloadConfigReq);
        }
        if (GUILayout.Button("重载脚本"))
        {

            ReloadLuaScripts req = new ReloadLuaScripts();
            req.Scripts.Add("_load_files_effect_script");
            req.Scripts.Add("_load_files_logic_net_handler");
            App.instance.net.gameSrv.Send(NetProto.PID.ReloadLuaScripts, req);
        }
        if (GUILayout.Button("重载本地脚本"))
        {
            Lua.LuaHelp.ReloadScripts("_load_files_map");
        }

        EditorGUILayout.EndHorizontal();
    }
}