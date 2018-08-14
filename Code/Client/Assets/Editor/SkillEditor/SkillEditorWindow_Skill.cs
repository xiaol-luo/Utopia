using Config;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        void SkillTabLogicImpl()
        {
            SkillTabData tabData = editorData.skillTabData;
            using (new GUILayout.HorizontalScope())
            {
                {
                    var sceneNames = tabData.GetSkillNames().ToArray();
                    var sceneIds = tabData.GetSkillIds().ToArray();
                    int oldCfgId = tabData.selectedSkillCfgId;
                    tabData.selectedSkillCfgId = EditorGUILayout.IntPopup(tabData.selectedSkillCfgId, sceneNames, sceneIds);
                    if (oldCfgId != tabData.selectedSkillCfgId)
                    {
                        tabData.selectedSkillLvlIdx = 0;
                    }
                }

                if (GUILayout.Button("new skill"))
                {
                    int nextId = tabData.GetNextSkillCfgId();
                    var newCfg = new Config.SkillConfig()
                    {
                        id = nextId,
                        name = string.Format("skill_{0}", nextId)
                    };
                    tabData.skillConfigs.cfgs.Add(newCfg);
                    tabData.selectedSkillCfgId = newCfg.id;
                    tabData.selectedSkillLvlIdx = 0;
                }
                if (GUILayout.Button("delete skill"))
                {
                    var skillCfg = tabData.GetSkillConfig(tabData.selectedSkillCfgId);
                    if (null != skillCfg)
                    {
                        tabData.skillConfigs.cfgs.Remove(skillCfg);
                    }
                }
            }

            var currSkillCfg = tabData.GetSkillConfig(tabData.selectedSkillCfgId);
            if (null == currSkillCfg)
                return;

            using (new GUILayout.VerticalScope())
            {
                float defaultLabelWidth = EditorGUIUtility.labelWidth;
                EditorGUIUtility.labelWidth = 120;

                currSkillCfg.id = EditorGUILayout.IntField("id", currSkillCfg.id);
                tabData.selectedSkillCfgId = currSkillCfg.id;

                currSkillCfg.name = EditorGUILayout.TextField("name", currSkillCfg.name);
                currSkillCfg.is_normal_attack = SkillEditorWindow.BoolPopup("normal attack", currSkillCfg.is_normal_attack);
                currSkillCfg.use_way = (Config.SkillConfig.UseWay)EditorGUILayout.EnumPopup("use way", currSkillCfg.use_way);
                currSkillCfg.target_type_flag = (Config.SkillConfig.TargetType)EditorGUILayout.EnumMaskPopup("target type", currSkillCfg.target_type_flag);
                currSkillCfg.target_relation_flag = (Config.SkillConfig.TargetRelation)EditorGUILayout.EnumMaskPopup("target relation", currSkillCfg.target_relation_flag);

                EditorGUILayout.PrefixLabel("level config");
                using (new EditorGUILayout.HorizontalScope())
                {
                    {
                        string[] lvlTxts = new string[currSkillCfg.lvl_cfgs.Count];
                        for (int i = 0; i < lvlTxts.Length; ++ i)
                        {
                            lvlTxts[i] = string.Format("lvl.{0}", i);
                        }
                        tabData.selectedSkillLvlIdx = EditorGUILayout.Popup("level config", tabData.selectedSkillLvlIdx, lvlTxts);
                    }
                    if (GUILayout.Button("new"))
                    {
                        Config.SkillLevelConfig newLvlCfg = null;
                        if (currSkillCfg.lvl_cfgs.Count > 0)
                            newLvlCfg = currSkillCfg.lvl_cfgs[currSkillCfg.lvl_cfgs.Count - 1].CloneSelf();
                        else
                            newLvlCfg = new Config.SkillLevelConfig();
                        currSkillCfg.lvl_cfgs.Add(newLvlCfg);
                        tabData.selectedSkillLvlIdx = currSkillCfg.lvl_cfgs.Count;
                    }
                    if (GUILayout.Button("delete"))
                    {
                        if (tabData.selectedSkillLvlIdx >= 0 && tabData.selectedSkillLvlIdx < currSkillCfg.lvl_cfgs.Count)
                        {
                            currSkillCfg.lvl_cfgs.RemoveAt(tabData.selectedSkillLvlIdx);
                            if (tabData.selectedSkillLvlIdx > 0)
                                tabData.selectedSkillLvlIdx -= 1;
                        }
                    }
                }
                
                if (currSkillCfg.lvl_cfgs.Count > 0)
                {

                    if (tabData.selectedSkillLvlIdx >= currSkillCfg.lvl_cfgs.Count)
                        tabData.selectedSkillLvlIdx = currSkillCfg.lvl_cfgs.Count - 1;
                    SkillLevelConfig lvlCfg = currSkillCfg.lvl_cfgs[tabData.selectedSkillLvlIdx];

                    lvlCfg.preparing_span = EditorGUILayout.IntField("preparing span", lvlCfg.preparing_span);
                    lvlCfg.releasing_span = EditorGUILayout.IntField("releasing span", lvlCfg.releasing_span);
                    lvlCfg.lasting_span = EditorGUILayout.IntField("lasting span", lvlCfg.lasting_span);
                    lvlCfg.consume_mp = EditorGUILayout.IntField("consume mp", lvlCfg.consume_mp);
                    lvlCfg.cd = EditorGUILayout.IntField("cd", lvlCfg.cd);
                    lvlCfg.cast_distance = EditorGUILayout.FloatField("cast distance", lvlCfg.cast_distance);
                    lvlCfg.can_move = SkillEditorWindow.BoolPopup("can move", lvlCfg.can_move);
                    lvlCfg.effect_id = EditorGUILayout.IntField("effect id", lvlCfg.effect_id);
                }
                EditorGUIUtility.labelWidth = defaultLabelWidth;
            }
        }

    }
}