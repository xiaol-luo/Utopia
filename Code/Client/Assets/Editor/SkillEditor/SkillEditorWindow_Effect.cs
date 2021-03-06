using Config;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        void EffectTabLogicImpl()
        {
            var tabData = editorData.effectTabData;

            using (new EditorGUILayout.HorizontalScope())
            {
                tabData.selectedEffectType = (EffectType)EditorGUILayout.EnumPopup("类型", tabData.selectedEffectType);
            }
            EditorGUILayout.Separator();
            EditorGUILayout.Space();

            using (new EditorGUILayout.VerticalScope())
            {
                tabData.ImplEditorLogic();
            }
        }
    }
}