using Config;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        void SceneUnitTabLogicImpl()
        {
            SceneUnitTabData suTabData = editorData.suTabData;

            using (new GUILayout.HorizontalScope())
            {
                {
                    var sceneNames = suTabData.GetSuNames().ToArray();
                    var sceneIds = suTabData.GetSuIds().ToArray();
                    suTabData.selectedSuCfgId = EditorGUILayout.IntPopup(suTabData.selectedSuCfgId, sceneNames, sceneIds);
                }

                if (GUILayout.Button("new scene"))
                {
                    int nextCfgId = suTabData.GetNextSuCfgId();
                    var newCfg = new Config.SceneUnitConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("scene_unit_{0}", nextCfgId)
                    };
                    suTabData.suConfig.cfgs.Add(newCfg);
                    suTabData.selectedSuCfgId = nextCfgId;
                }
                if (GUILayout.Button("delete scene"))
                {
                    var suCfg = suTabData.GetSuConfig(suTabData.selectedSuCfgId);
                    if (null != suCfg)
                    {
                        suTabData.suConfig.cfgs.Remove(suCfg);
                    }
                }
            }

            SceneUnitConfig currSuCfg = suTabData.GetSuConfig(suTabData.selectedSuCfgId);
            if (null == currSuCfg)
                return;

            using (new GUILayout.HorizontalScope())
            {
                using (new GUILayout.VerticalScope())
                {
                    float defaultLabelWidth = EditorGUIUtility.labelWidth;
                    EditorGUIUtility.labelWidth = 120;

                    currSuCfg.id = EditorGUILayout.IntField("id", currSuCfg.id);
                    currSuCfg.name = EditorGUILayout.TextField("name", currSuCfg.name);
                    currSuCfg.hp = EditorGUILayout.IntField("hp", currSuCfg.hp);
                    currSuCfg.mp = EditorGUILayout.IntField("mp", currSuCfg.mp);
                    currSuCfg.attack = EditorGUILayout.IntField("attack", currSuCfg.attack);

                    {
                        var skillNames = editorData.skillTabData.GetSkillNames().ToArray();
                        var skillIds = editorData.skillTabData.GetSkillIds().ToArray();
                        currSuCfg.q_skill_id = EditorGUILayout.IntPopup("q skill id", currSuCfg.q_skill_id, skillNames, skillIds);
                        currSuCfg.w_skill_id = EditorGUILayout.IntPopup("w skill id", currSuCfg.w_skill_id, skillNames, skillIds);
                        currSuCfg.e_skill_id = EditorGUILayout.IntPopup("e skill id", currSuCfg.e_skill_id, skillNames, skillIds);
                        currSuCfg.r_skill_id = EditorGUILayout.IntPopup("r skill id", currSuCfg.r_skill_id, skillNames, skillIds);
                    }

                    EditorGUIUtility.labelWidth = defaultLabelWidth;
                }
            }
        }
    }
}