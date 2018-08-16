using Config;
using System;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public class SearcherEffectEditor : EffectEditorBase
    {
        public SearcherEffectEditor(EffectTabData _tabData) : base(_tabData)
        {
        }

        public const string CONFIG_PATH = "skill_editor/effect/searcher_effect.json";
        public string cfgPath
        {
            get
            {
                string ret = Path.Combine(tabData.editorData.jsonCfgPath, CONFIG_PATH);
                return ret;
            }
        }

        AllEffectSearcherConfig _allCfgs = null;
        AllEffectSearcherConfig allCfgs
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
            _allCfgs = JsonHelp.LoadStruct<AllEffectSearcherConfig>(cfgPath);
        }

        public override bool SaveCfgs()
        {
            var toSave = (null != _allCfgs ? _allCfgs : new AllEffectSearcherConfig());
            bool ret = JsonHelp.SaveStruct(cfgPath, toSave);
            return ret;
        }

        public override ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = new ConfigIdNameListStruct();
            allCfgs.cfgs.ForEach((EffectSearcherConfig cfg) => { ret.ids.Add(cfg.id); ret.names.Add(cfg.name); });
            return ret;
        }

        public int selectedCfgId = 0;
        public override void ImplEditorLogic()
        {
            using (new GUILayout.HorizontalScope())
            {
                {
                    ConfigIdNameListStruct idNameList = this.GetCfgIdNameList(null);
                    selectedCfgId = EditorGUILayout.IntPopup(selectedCfgId, idNameList.names.ToArray(), idNameList.ids.ToArray());
                }

                if (GUILayout.Button("new"))
                {
                    int nextCfgId = this.GetNextCfgId();
                    var newCfg = new Config.EffectSearcherConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("searcher_effect_{0}", nextCfgId)
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
            }

            var currCfg = this.GetConfig(selectedCfgId);
            if (null == currCfg)
                return;

            using (new EditorGUILayout.VerticalScope())
            {
                currCfg.id = EditorGUILayout.IntField("id", currCfg.id);
                currCfg.name = EditorGUILayout.TextField("name", currCfg.name);

                {
                    var filterIds = tabData.editorData.filterTabData.GetCfgIds().ToArray();
                    var filterNames = tabData.editorData.filterTabData.GetCfgNames().ToArray();
                    currCfg.filter_id = EditorGUILayout.IntPopup("filter", currCfg.filter_id, filterNames, filterIds);
                }

                EditorGUILayout.LabelField("Attach Effects");
                if (GUILayout.Button("New"))
                {
                    currCfg.effect_ids.Add(0);
                }
                for (int i = 0; i < currCfg.effect_ids.Count; ++i)
                {
                    using (new EditorGUILayout.HorizontalScope())
                    {
                        currCfg.effect_ids[i] = EditorGUILayout.IntField("effect id", currCfg.effect_ids[i]);
                        if (GUILayout.Button("delete"))
                        {
                            currCfg.effect_ids.RemoveAt(i);
                            break;
                        }
                    }
                }
            }
        }

        int AllowCalMinCfgId()
        {
            return (int)EffectType.Seacher * EffectEditorBase.EFFECT_CONFIG_ID_GAP;
        }

        int GetNextCfgId()
        {
            int maxId = 0;
            allCfgs.cfgs.ForEach((EffectSearcherConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            int allowMinCfgId = this.AllowCalMinCfgId();
            if (maxId < allowMinCfgId)
                maxId = allowMinCfgId;
            return maxId + 1;
        }

        public EffectSearcherConfig GetConfig(int id)
        {
            var ret = allCfgs.cfgs.Find((EffectSearcherConfig cfg) => { return cfg.id == id; });
            return ret;
        }
    }
}