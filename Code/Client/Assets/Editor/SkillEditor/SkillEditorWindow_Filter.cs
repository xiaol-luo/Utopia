using Config;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        void FilterTabLogicImpl()
        {
            var tabData = editorData.filterTabData;

            using (new GUILayout.HorizontalScope())
            {
                {
                    var cfgNames = tabData.GetCfgNames().ToArray();
                    var cfgIds = tabData.GetCfgIds().ToArray();
                    tabData.selectedCfgId = EditorGUILayout.IntPopup(tabData.selectedCfgId, cfgNames, cfgIds);
                }

                if (GUILayout.Button("new scene"))
                {
                    int nextCfgId = tabData.GetNextCfgId();
                    var newCfg = new Config.SuFilterConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("filter_{0}", nextCfgId)
                    };
                    tabData.allCfgs.cfgs.Add(newCfg);
                    tabData.selectedCfgId = nextCfgId;
                }
                if (GUILayout.Button("delete scene"))
                {
                    var suCfg = tabData.GetConfig(tabData.selectedCfgId);
                    if (null != suCfg)
                    {
                        tabData.allCfgs.cfgs.Remove(suCfg);
                    }
                }
            }

            var currSuCfg = tabData.GetConfig(tabData.selectedCfgId);
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
                    currSuCfg.limit_num = EditorGUILayout.IntField("limit num", currSuCfg.limit_num);
                    currSuCfg.limit_num_priority = (EEffectFilterLimitNumPriority)EditorGUILayout.EnumPopup("limit num priority", currSuCfg.limit_num_priority);
                    currSuCfg.unit_type_flag = (SceneUnitType)EditorGUILayout.EnumMaskPopup("unit type", currSuCfg.unit_type_flag);
                    currSuCfg.relation_flag = (SceneUnitRelation)EditorGUILayout.EnumMaskPopup("relations", currSuCfg.relation_flag);
                    currSuCfg.anchor = (EEffectFilterAnchor)EditorGUILayout.EnumPopup("anchor", currSuCfg.anchor);
                    currSuCfg.shape_type = (EEffectFilterShape)EditorGUILayout.EnumPopup("shape type", currSuCfg.shape_type);

                    switch (currSuCfg.shape_type)
                    {
                        case EEffectFilterShape.Circle:
                            {
                                currSuCfg.shape_circle = EditorGUILayout.FloatField("radio", currSuCfg.shape_circle);
                            }
                            break;
                        case EEffectFilterShape.Rect:
                            {
                                currSuCfg.shape_rect = SkillEditorWindow.Vector2Field("rect", currSuCfg.shape_rect);
                            }
                            break;
                        case EEffectFilterShape.Sector:
                            {
                                currSuCfg.shape_sector = SkillEditorWindow.Vector2Field("radio, angle", currSuCfg.shape_sector);
                            }
                            break;
                    }

                    EditorGUIUtility.labelWidth = defaultLabelWidth;
                }
            }
        }
    }
}