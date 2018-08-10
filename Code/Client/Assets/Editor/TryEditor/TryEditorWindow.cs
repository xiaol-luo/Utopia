using UnityEditor;
using UnityEngine;

namespace TryEditor
{
    public class TryEditorWindow : EditorWindow
    {
        [MenuItem("Tools/TryEditorWindow", false, 200)]
        public static void OpenWindow()
        {
            var window = EditorWindow.GetWindow<TryEditorWindow>("TryEditorWindow");
            window.minSize = new Vector2(720.0f, 480.0f);
            window.autoRepaintOnSceneChange = true;
            window.wantsMouseEnterLeaveWindow = true;
            window.wantsMouseMove = true;
        }
        private void Awake()
        {
            Debug.Log("TryEditorWindow::Awake");
        }

        private void OnEnable()
        {
            Debug.Log("TryEditorWindow::OnEnable");
        }

        private void OnDisable()
        {
            Debug.Log("TryEditorWindow::OnDisable");
        }

        private void Update()
        {
            // Debug.Log("TryEditorWindow::Update");
        }
        private void OnGUI()
        {
            // Debug.Log("TryEditorWindow::OnGUI");
            this.Test();
        }
        private void OnInspectorUpdate()
        {
            // Debug.Log("TryEditorWindow::OnInspectorUpdate");
        }

        private void OnFocus()
        {
            Debug.Log("TryEditorWindow::OnFocus");
        }

        private void OnLostFocus()
        {
            Debug.Log("TryEditorWindow::OnLostFocus");
        }

        private void OnDestroy()
        {
            Debug.Log("TryEditorWindow::OnDestroy");
        }

        private void OnHierarchyChange()
        {
            Debug.Log("TryEditorWindow::OnHierarchyChange");
        }
        private void OnProjectChange()
        {
            Debug.Log("TryEditorWindow::OnProjectChange");
        }

        // void Test
        void Test()
        {
            EditorGUILayout.BeginVertical(EditorStyles.textArea);

            EditorGUILayout.TextArea(string.Format("EditorApplication.applicationContentsPath: {0}", EditorApplication.applicationContentsPath));
            EditorGUILayout.TextArea(string.Format("EditorApplication.applicationPath: {0}", EditorApplication.applicationPath));

            EditorGUILayout.TextArea(string.Format("Application.applicationPath: {0}", Application.dataPath));
            EditorGUILayout.TextArea(string.Format("Application.persistentDataPath: {0}", Application.persistentDataPath));
            EditorGUILayout.TextArea(string.Format("Application.streamingAssetsPath: {0}", Application.streamingAssetsPath));
            EditorGUILayout.TextArea(string.Format("Application.temporaryCachePath: {0}", Application.temporaryCachePath));
            EditorGUILayout.BeginVertical();
        }
    }
}