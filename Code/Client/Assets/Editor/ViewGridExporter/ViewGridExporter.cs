
using UnityEditor;
using UnityEngine;

namespace CustomEditor
{
    class ViewGridExporter
    {
        [MenuItem("Custom/ViewGrid/Save")]
        static void Save()
        {
            GameObject root = GameObject.Find("ViewGridEditor");
            ViewGridEditor[] objs = GameObject.FindObjectsOfType<ViewGridEditor>();
            if (null == objs || objs.Length <= 0)
                return;

            objs[0].Save("eos_navmesh.view");
            EditorUtility.DisplayDialog("��ʾ", "��ͼ���ñ������", "Ok");
        }
    }
}