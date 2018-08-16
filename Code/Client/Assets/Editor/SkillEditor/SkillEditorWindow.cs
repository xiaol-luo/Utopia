using Config;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        [MenuItem("Tools/SkillEditorWindow")]
        public static void OpenWindow()
        {
            var window = EditorWindow.GetWindowWithRect<SkillEditorWindow>(
                new Rect(
                    (Screen.width - SkillEditorWindowData.WINDOW_FIX_WIDTH) / 2,
                    (Screen.height - SkillEditorWindowData.WINDOW_MIN_HEIGHT) / 2,
                    SkillEditorWindowData.WINDOW_FIX_WIDTH,
                    SkillEditorWindowData.WINDOW_MIN_HEIGHT
                    ));
            window.minSize = new Vector2(
                SkillEditorWindowData.WINDOW_FIX_WIDTH, 
                SkillEditorWindowData.WINDOW_MIN_HEIGHT);
            window.autoRepaintOnSceneChange = true;
            window.wantsMouseEnterLeaveWindow = true;
            window.wantsMouseMove = true;


        }

        public SkillEditorWindowData editorData = null;

        private void OnEnable()
        {
            Debug.Log("SkillEditorWindow::OnEnable");
            editorData = new SkillEditorWindowData();
            editorData.tabSettings = new SkillEditorTabSetting[TopTabIdx.COUNT]
            {
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SCENE, tabName="scene", logicImpl=SceneTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SCENE_UNIT, tabName="su", logicImpl=SceneUnitTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SKILL, tabName="skill", logicImpl=SkillTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.FILTER, tabName="filter", logicImpl=FilterTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.EFFECT_GROUP, tabName="effect group", logicImpl=EffectGroupTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.EFFECT, tabName="effect", logicImpl=EffectTabLogicImpl},
            };
            editorData.LoadAllCfg();
        }

        private void OnDisable()
        {
            Debug.Log("SkillEditorWindow::OnDisable");
            editorData.SaveAllCfg();
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
                new Rect(0, 0, SkillEditorWindowData.WINDOW_FIX_WIDTH, SkillEditorWindowData.WINDOW_MIN_HEIGHT), 
                "skill editor"))
            {
                using (new EditorGUILayout.VerticalScope())
                {
                    using (new GUILayout.HorizontalScope(EditorStyles.toolbarButton))
                    {
                        string[] topToolbarTexts = new string[editorData.tabSettings.Length];
                        for (int i = 0; i < editorData.tabSettings.Length; ++i)
                        {
                            topToolbarTexts[i] = editorData.tabSettings[i].tabName;
                        }
                        editorData.topToobardx = GUILayout.Toolbar(editorData.topToobardx, topToolbarTexts);
                    }

                    EditorGUILayout.Space();

                    if (editorData.topToobardx >= 0 && editorData.topToobardx < editorData.tabSettings.Length)
                    {
                        using (new EditorGUILayout.VerticalScope())
                        {
                            editorData.tabSettings[editorData.topToobardx].logicImpl();
                        }
                    } 
                }
            }
        }

        void NoneLogicImpl()
        {

        }

        public static bool BoolPopup(string label, bool val, params GUILayoutOption[] options)
        {
            int[]vals = new int[2] { 0, 1};
            string[] strs = new string[2] { "false", "true" };
            int ret = EditorGUILayout.IntPopup(label, val ? 1 : 0, strs, vals, options);
            return 0 != ret;
        }

        public static JsonVector2 Vector2Field(string label, JsonVector2 jsonVec2, params GUILayoutOption[] options)
        {
            Vector2 vec2 = jsonVec2.MakeVector2();
            vec2 = EditorGUILayout.Vector2Field("rect", vec2);
            return new JsonVector2(vec2);
        }
    }
}