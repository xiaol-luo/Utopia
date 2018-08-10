using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        [MenuItem("Tools/SkillEditorWindow")]
        public static void OpenWindow()
        {
            var window = EditorWindow.GetWindow<SkillEditorWindow>("SkillEditorWindow");
            window.minSize = new Vector2(SkillEditorWindowData.WINDOW_FIX_WIDTH, SkillEditorWindowData.WINDOW_MIN_HEIGHT);
            window.autoRepaintOnSceneChange = true;
            window.wantsMouseEnterLeaveWindow = true;
            window.wantsMouseMove = true;


        }

        public SkillEditorWindowData editorData = null;
        string[] topToolbarTexts = null;
        private void Awake()
        {
            Debug.Log("SkillEditorWindow::Awake");

            editorData = new SkillEditorWindowData();
            editorData.tabSettings = new SkillEditorTabSetting[TopTabIdx.COUNT]
            {
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SCENE, tabName="scene", logicImpl=NoneLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SCENE_UNIT, tabName="su", logicImpl=NoneLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SKILL, tabName="skill", logicImpl=NoneLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.EFFECT, tabName="effect", logicImpl=NoneLogicImpl},
            };

            topToolbarTexts = new string[editorData.tabSettings.Length];
            for (int i = 0; i < editorData.tabSettings.Length; ++ i)
            {
                topToolbarTexts[i] = editorData.tabSettings[i].tabName;
            }
        }

        private void OnEnable()
        {
            Debug.Log("SkillEditorWindow::OnEnable");
        }

        private void OnDisable()
        {
            Debug.Log("SkillEditorWindow::OnDisable");
        }
        private void OnGUI()
        {
            // Debug.Log("SkillEditorWindow::OnGUI");
            this.LogicImpl();
        }
        // void Test
        void LogicImpl()
        {
            using (new GUILayout.AreaScope(
                new Rect(Screen.width / 2, Screen.height / 2, SkillEditorWindowData.WINDOW_FIX_WIDTH, SkillEditorWindowData.WINDOW_MIN_HEIGHT), 
                "skill editor"))
            {
                using (new GUILayout.HorizontalScope())
                {
                    editorData.topToobardx = GUILayout.Toolbar(editorData.topToobardx, topToolbarTexts);
                }
            }

            EditorGUILayout.BeginVertical(EditorStyles.textArea);

            EditorGUILayout.TextArea(string.Format("EditorApplication.applicationContentsPath: {0}", EditorApplication.applicationContentsPath));
            EditorGUILayout.TextArea(string.Format("EditorApplication.applicationPath: {0}", EditorApplication.applicationPath));

            EditorGUILayout.TextArea(string.Format("Application.applicationPath: {0}", Application.dataPath));
            EditorGUILayout.TextArea(string.Format("Application.persistentDataPath: {0}", Application.persistentDataPath));
            EditorGUILayout.TextArea(string.Format("Application.streamingAssetsPath: {0}", Application.streamingAssetsPath));
            EditorGUILayout.TextArea(string.Format("Application.temporaryCachePath: {0}", Application.temporaryCachePath));
            EditorGUILayout.BeginVertical();
        }

        void NoneLogicImpl()
        {

        }
    }
}