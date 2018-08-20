using Config;
using System;
using System.Collections.Generic;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public class GroupEffectEditor : EffectEditorBase
    {
        public GroupEffectEditor(EffectTabData _tabData) : base(_tabData)
        {
        }

        public const string CONFIG_PATH = "skill_editor/effect/effect_group_config.json";
        public string cfgPath
        {
            get
            {
                string ret = Path.Combine(tabData.editorData.jsonCfgPath, CONFIG_PATH);
                return ret;
            }
        }

        AllEffectGroupConfig _allCfgs = null;
        AllEffectGroupConfig allCfgs
        {
            get
            {
                if (null == _allCfgs)
                {
                    this.LoadCfgs();
                }
                return _allCfgs;
            }
            set
            {
                _allCfgs = value;
            }
        }
        public override void LoadCfgs()
        {
            _allCfgs = JsonHelp.LoadStruct<AllEffectGroupConfig>(cfgPath);
        }

        public override bool SaveCfgs()
        {
            var toSave = (null != _allCfgs ? _allCfgs : new AllEffectGroupConfig());
            bool ret = JsonHelp.SaveStruct(cfgPath, toSave);
            return ret;
        }

        public override ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = new ConfigIdNameListStruct();
            allCfgs.cfgs.ForEach((EffectGroupConfig cfg) => { ret.ids.Add(cfg.id); ret.names.Add(cfg.name); });
            return ret;
        }

        public int selectedCfgId = 0;
        public List<EffectType> cachedBeginEffectSelectedTypes = new List<EffectType>();
        public List<EffectType> cachedEndEffectSelectedTypes = new List<EffectType>();
        public List<EffectType> cachedTimelineEffectSelectedTypes = new List<EffectType>();
        public override void ImplEditorLogic()
        {
            using (new GUILayout.HorizontalScope())
            {
                int oldSelectedCfgId = selectedCfgId;
                {
                    ConfigIdNameListStruct idNameList = this.GetCfgIdNameList(null);
                    selectedCfgId = EditorGUILayout.IntPopup(selectedCfgId, idNameList.names.ToArray(), idNameList.ids.ToArray());
                }

                if (GUILayout.Button("new"))
                {
                    int nextCfgId = this.GetNextCfgId();
                    var newCfg = new Config.EffectGroupConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("hurt_effect_{0}", nextCfgId)
                    };
                    this.allCfgs.cfgs.Add(newCfg);
                    this.selectedCfgId = nextCfgId;
                }
                if (GUILayout.Button("delete"))
                {
                    var toDelCfg = this.GetConfig(this.selectedCfgId);
                    if (null != toDelCfg)
                    {
                        this.allCfgs.cfgs.Remove(toDelCfg);
                    }
                }
                if (oldSelectedCfgId != selectedCfgId)
                {
                    for (int i = 0; i < cachedBeginEffectSelectedTypes.Count; ++i)
                    {
                        cachedBeginEffectSelectedTypes[i] = EffectType.Count;
                    }
                    for (int i = 0; i < cachedEndEffectSelectedTypes.Count; ++i)
                    {
                        cachedEndEffectSelectedTypes[i] = EffectType.Count;
                    }
                    for (int i = 0; i < cachedTimelineEffectSelectedTypes.Count; ++i)
                    {
                        cachedTimelineEffectSelectedTypes[i] = EffectType.Count;
                    }
                }
            }

            var currCfg = this.GetConfig(selectedCfgId);
            if (null == currCfg)
                return;

            using (new EditorGUILayout.VerticalScope())
            {
                currCfg.id = EditorGUILayout.IntField("id", currCfg.id);
                currCfg.name = EditorGUILayout.TextField("name", currCfg.name);
                currCfg.need_guide = SkillEditorWindow.BoolPopup("need guild", currCfg.need_guide);
                currCfg.can_cancel_guide = SkillEditorWindow.BoolPopup("can cancel guild", currCfg.can_cancel_guide);

                EditorGUILayout.LabelField("Begin Effects");
                if (GUILayout.Button("add begin effect"))
                {
                    currCfg.begin_effect_ids.Add(0);
                }
                while (cachedBeginEffectSelectedTypes.Count < currCfg.begin_effect_ids.Count)
                {
                    cachedBeginEffectSelectedTypes.Add(EffectType.Count);
                }
                for (int i = 0; i < currCfg.begin_effect_ids.Count; ++i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        List<EffectType> selectedTypes = cachedBeginEffectSelectedTypes;
                        var ret = SkillEditorWindow.PopupSkillSelecter(tabData.editorData, currCfg.begin_effect_ids[i], selectedTypes[i]);
                        currCfg.begin_effect_ids[i] = ret.effect_id;
                        selectedTypes[i] = ret.effect_type;
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.begin_effect_ids.RemoveAt(i);
                            selectedTypes.RemoveAt(i);
                            break;
                        }
                        /*
                        currCfg.begin_effect_ids[i] = EditorGUILayout.IntField("begin effect id", currCfg.begin_effect_ids[i]);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.begin_effect_ids.RemoveAt(i);
                            break;
                        }
                        */
                    }
                }

                EditorGUILayout.LabelField("End Effects");
                if (GUILayout.Button("add end effect"))
                {
                    currCfg.end_effect_ids.Add(new EncCaseEffectStruct());
                }
                while (cachedEndEffectSelectedTypes.Count < currCfg.end_effect_ids.Count)
                {
                    cachedEndEffectSelectedTypes.Add(EffectType.Count);
                }
                for (int i = 0; i < currCfg.end_effect_ids.Count; ++i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        /*
                        currCfg.end_effect_ids[i].effect_id = EditorGUILayout.IntField("effect id", currCfg.end_effect_ids[i].effect_id);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.end_effect_ids.RemoveAt(i);
                            break;
                        }
                        */

                        List<EffectType> selectedTypes = cachedEndEffectSelectedTypes;
                        var ret = SkillEditorWindow.PopupSkillSelecter(tabData.editorData, currCfg.end_effect_ids[i].effect_id, selectedTypes[i]);
                        currCfg.end_effect_ids[i].effect_id = ret.effect_id;
                        selectedTypes[i] = ret.effect_type;
                        float defaultLabelWidth = EditorGUIUtility.labelWidth;
                        EditorGUIUtility.labelWidth = 60;
                        currCfg.end_effect_ids[i].end_case = (EffectEndCase)EditorGUILayout.EnumPopup("end case", currCfg.end_effect_ids[i].end_case);
                        EditorGUIUtility.labelWidth = defaultLabelWidth;
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.end_effect_ids.RemoveAt(i);
                            selectedTypes.RemoveAt(i);
                            break;
                        }
                    }
                }
                EditorGUILayout.LabelField("Timeline Effects");
                if (GUILayout.Button("add timeline effect"))
                {
                    currCfg.timeline_effect_ids.Add(new TimeLineEffectStruct());
                }
                while (cachedTimelineEffectSelectedTypes.Count < currCfg.timeline_effect_ids.Count)
                {
                    cachedTimelineEffectSelectedTypes.Add(EffectType.Count);
                }
                for (int i = 0; i < currCfg.timeline_effect_ids.Count; ++i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        /*
                        currCfg.timeline_effect_ids[i].effect_id = EditorGUILayout.IntField("effect id", currCfg.timeline_effect_ids[i].effect_id);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.timeline_effect_ids.RemoveAt(i);
                            break;
                        }
                        */
                        List<EffectType> selectedTypes = cachedTimelineEffectSelectedTypes;
                        var ret = SkillEditorWindow.PopupSkillSelecter(tabData.editorData, currCfg.timeline_effect_ids[i].effect_id, selectedTypes[i]);
                        currCfg.timeline_effect_ids[i].effect_id = ret.effect_id;
                        selectedTypes[i] = ret.effect_type;
                        float defaultLabelWidth = EditorGUIUtility.labelWidth;
                        EditorGUIUtility.labelWidth = 60;
                        currCfg.timeline_effect_ids[i].begin_ms = EditorGUILayout.IntField("begin ms", currCfg.timeline_effect_ids[i].begin_ms);
                        EditorGUIUtility.labelWidth = defaultLabelWidth;
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.timeline_effect_ids.RemoveAt(i);
                            selectedTypes.RemoveAt(i);
                            break;
                        }
                    }
                }
            }
        }

        int AllowCalMinCfgId()
        {
            return (int)EffectType.Group * EffectEditorBase.EFFECT_CONFIG_ID_GAP;
        }

        int GetNextCfgId()
        {
            int maxId = 0;
            allCfgs.cfgs.ForEach((EffectGroupConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            int allowMinCfgId = this.AllowCalMinCfgId();
            if (maxId < allowMinCfgId)
                maxId = allowMinCfgId;
            return maxId + 1;
        }

        public EffectGroupConfig GetConfig(int id)
        {
            var ret = allCfgs.cfgs.Find((EffectGroupConfig cfg) => { return cfg.id == id; });
            return ret;
        }
        public override EffectConfigBase GetCfg(int id)
        {
            return this.GetConfig(id);
        }
    }
}