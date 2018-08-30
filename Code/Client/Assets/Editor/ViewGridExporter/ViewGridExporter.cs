
using UnityEditor;
using UnityEngine;

namespace CustomEditor
{
    class ViewGridExporter
    {
        [MenuItem("Tools/ViewGrid/Save")]
        static void Save()
        {
            GameObject root = GameObject.Find("ViewGridEditor");
            ViewGridEditor[] objs = GameObject.FindObjectsOfType<ViewGridEditor>();
            if (null == objs || objs.Length <= 0)
                return;

            objs[0].Save("eos_navmesh.view");
            EditorUtility.DisplayDialog("提示", "视图配置保存完毕", "Ok");
        }
    }
}