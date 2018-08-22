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
            ResetEditorData();
        }

        public void ResetEditorData()
        {
            editorData = new SkillEditorWindowData();
            editorData.tabSettings = new SkillEditorTabSetting[TopTabIdx.COUNT]
            {
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.EFFECT, tabName="effect", logicImpl=EffectTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.FILTER, tabName="filter", logicImpl=FilterTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SKILL, tabName="skill", logicImpl=SkillTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SCENE_UNIT, tabName="su", logicImpl=SceneUnitTabLogicImpl},
                new SkillEditorTabSetting(){tabIdx=TopTabIdx.SCENE, tabName="scene", logicImpl=SceneTabLogicImpl},
            };
            editorData.LoadAllCfg();
        }

        public void SaveAllConfigs()
        {
            if (null != editorData)
            {
                editorData.SaveAllCfg();
            }
        }

        private void OnDisable()
        {
            Debug.Log("SkillEditorWindow::OnDisable");
            // SaveAllConfigs();
        }
        private void OnGUI()
        {
            // Debug.Log("SkillEditorWindow::OnGUI");
            this.LogicImpl();
        }
        // void Test
        void LogicImpl()
        {
            // using (new GUILayout.AreaScope(new Rect(0, 0, SkillEditorWindowData.WINDOW_FIX_WIDTH, SkillEditorWindowData.WINDOW_MIN_HEIGHT)))
            {
                using (new EditorGUILayout.HorizontalScope())
                {
                    if (GUILayout.Button("reload all"))
                    {
                        this.ResetEditorData();
                    }
                    if (GUILayout.Button("save all"))
                    {
                        this.SaveAllConfigs();
                    }
                }
                EditorGUILayout.Space();

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
                EditorGUILayout.Separator();

                if (editorData.topToobardx >= 0 && editorData.topToobardx < editorData.tabSettings.Length)
                {
                    using (new EditorGUILayout.VerticalScope())
                    {
                        editorData.tabSettings[editorData.topToobardx].logicImpl();
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

        public class SelectEffectRet
        {
            public EffectType effect_type;
            public int effect_id;
        }

        public static SelectEffectRet PopupSkillSelecter(SkillEditorWindowData editorData, int effectId, EffectType effectType)
        {
            EffectTabData.EffectConfigDetail ed = editorData.effectTabData.GetEffecCfg(effectId);
            if (effectType >= EffectType.Count)
            {
                if (null != ed)
                {
                    effectType = ed.type;
                }
            }

            SelectEffectRet ret = new SelectEffectRet();

            float defaultLabelWidth = EditorGUIUtility.labelWidth;
            EditorGUIUtility.labelWidth = 40;
            using (new EditorGUILayout.HorizontalScope())
            {
                GUILayout.Label(null != ed.cfg ? ed.cfg.name : "None", GUILayout.Width(200));
                ret.effect_type = (EffectType)EditorGUILayout.EnumPopup("type", effectType);
                ConfigIdNameListStruct idNames = editorData.effectTabData.GetCfgIdNameList(effectType, null);
                ret.effect_id = EditorGUILayout.IntPopup("id", effectId, idNames.names.ToArray(), idNames.ids.ToArray());
            }
            EditorGUIUtility.labelWidth = defaultLabelWidth;

            return ret;
        }
    }
}