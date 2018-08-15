using Config;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        void EffectGroupTabLogicImpl()
        {
            EffectGroupTabData tabData = editorData.effectGroupTabData;
            using (new GUILayout.HorizontalScope())
            {
                {
                    var names = tabData.GetEffectGroupNames().ToArray();
                    var ids = tabData.GetEffectGroupIds().ToArray();
                    tabData.selectedEffectGroupCfgId = EditorGUILayout.IntPopup(tabData.selectedEffectGroupCfgId, names, ids);
                }

                if (GUILayout.Button("new"))
                {
                    int nextId = tabData.GetNextEffectGroupCfgId();
                    var newCfg = new Config.EffectGroupConfig()
                    {
                        id = nextId,
                        name = string.Format("effect_group_{0}", nextId)
                    };
                    tabData.effectGroupConfig.cfgs.Add(newCfg);
                    tabData.selectedEffectGroupCfgId = newCfg.id;
                }
                if (GUILayout.Button("delete skill"))
                {
                    var toDelCfg = tabData.GetEffectGroupConfig(tabData.selectedEffectGroupCfgId);
                    if (null != toDelCfg)
                    {
                        tabData.effectGroupConfig.cfgs.Remove(toDelCfg);
                    }
                }
            }

            var currCfg = tabData.GetEffectGroupConfig(tabData.selectedEffectGroupCfgId);
            if (null == currCfg)
                return;

            using (new GUILayout.VerticalScope())
            {
                float defaultLabelWidth = EditorGUIUtility.labelWidth;
                EditorGUIUtility.labelWidth = 120;

                currCfg.id = EditorGUILayout.IntField("id", currCfg.id);
                tabData.selectedEffectGroupCfgId= currCfg.id;
                currCfg.name = EditorGUILayout.TextField("name", currCfg.name);
                currCfg.need_guide = SkillEditorWindow.BoolPopup("need guild", currCfg.need_guide);
                currCfg.can_cancel_guide = SkillEditorWindow.BoolPopup("can cancel guild", currCfg.can_cancel_guide);

                EditorGUILayout.LabelField("Begin Effects");
                if (GUILayout.Button("add begin effect"))
                {
                    currCfg.begin_effect_ids.Add(0);
                }
                for (int i = 0; i < currCfg.begin_effect_ids.Count; ++ i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        currCfg.begin_effect_ids[i] = EditorGUILayout.IntField("begin effect id", currCfg.begin_effect_ids[i]);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.begin_effect_ids.RemoveAt(i);
                            break;
                        }
                    }
                }

                EditorGUILayout.LabelField("End Effects");
                if (GUILayout.Button("add end effect"))
                {
                    currCfg.end_effect_ids.Add(new EncCaseEffectStruct());
                }
                for (int i = 0; i < currCfg.end_effect_ids.Count; ++i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        currCfg.end_effect_ids[i].end_case = (EffectEndCase)EditorGUILayout.EnumPopup("end case", currCfg.end_effect_ids[i].end_case);
                        currCfg.end_effect_ids[i].effect_id = EditorGUILayout.IntField("effect id", currCfg.end_effect_ids[i].effect_id);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.end_effect_ids.RemoveAt(i);
                            break;
                        }
                    }
                }
                EditorGUILayout.LabelField("Timeline Effects");
                if (GUILayout.Button("add timeline effect"))
                {
                    currCfg.timeline_effect_ids.Add(new TimeLineEffectStruct());
                }
                for (int i = 0; i < currCfg.timeline_effect_ids.Count; ++i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        currCfg.timeline_effect_ids[i].begin_ms = EditorGUILayout.IntField("begin ms", currCfg.timeline_effect_ids[i].begin_ms);
                        currCfg.timeline_effect_ids[i].effect_id = EditorGUILayout.IntField("effect id", currCfg.timeline_effect_ids[i].effect_id);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.timeline_effect_ids.RemoveAt(i);
                            break;
                        }
                    }
                }
            }
        }
    }
}