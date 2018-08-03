using UnityEngine;
using UnityEditor;
using UnityEngine.UI;
using Utopia;
using Utopia.Logic;

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
        EditorGUILayout.EndHorizontal();
    }
}