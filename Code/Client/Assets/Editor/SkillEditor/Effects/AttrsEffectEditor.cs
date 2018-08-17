using Config;
using System;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public class AttrsEffectEditor : EffectEditorBase
    {
        public AttrsEffectEditor(EffectTabData _tabData) : base(_tabData)
        {
        }

        public const string CONFIG_PATH = "skill_editor/effect/attrs_effect.json";
        public string cfgPath
        {
            get
            {
                string ret = Path.Combine(tabData.editorData.jsonCfgPath, CONFIG_PATH);
                return ret;
            }
        }

        AllAttrsEffectConfig _allCfgs = null;
        AllAttrsEffectConfig allCfgs
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
            _allCfgs = JsonHelp.LoadStruct<AllAttrsEffectConfig>(cfgPath);
        }

        public override bool SaveCfgs()
        {
            var toSave = (null != _allCfgs ? _allCfgs : new AllAttrsEffectConfig());
            bool ret = JsonHelp.SaveStruct(cfgPath, toSave);
            return ret;
        }

        public override ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = new ConfigIdNameListStruct();
            allCfgs.cfgs.ForEach((AttrsEffectConfig cfg) => { ret.ids.Add(cfg.id); ret.names.Add(cfg.name); });
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
                    var newCfg = new Config.AttrsEffectConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("attrs_effect_{0}", nextCfgId)
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
                    // 基础属性
                    var attrs = currCfg.base_attrs;
                    EditorGUILayout.LabelField("Base Attributes");
                    if (GUILayout.Button("New"))
                    {
                        attrs.Add(new AttrKvStruct());
                    }
                    for (int i = 0; i < attrs.Count; ++i)
                    {
                        using (new EditorGUILayout.HorizontalScope())
                        {
                            attrs[i].efp = (NetProto.EFightParam)EditorGUILayout.EnumPopup("attr id", attrs[i].efp);
                            attrs[i].val = EditorGUILayout.IntField("value", attrs[i].val);
                            attrs[i].unique_id = EditorGUILayout.IntField("unique_id", attrs[i].unique_id);
                            if (GUILayout.Button("delete"))
                            {
                                attrs.RemoveAt(i);
                                break;
                            }
                        }
                    }
                }

                {
                    // 百分比属性
                    var attrs = currCfg.percent_attrs;
                    EditorGUILayout.LabelField("Percent Attributes");
                    if (GUILayout.Button("New"))
                    {
                        attrs.Add(new AttrKvStruct());
                    }
                    for (int i = 0; i < attrs.Count; ++i)
                    {
                        using (new EditorGUILayout.HorizontalScope())
                        {
                            attrs[i].efp = (NetProto.EFightParam)EditorGUILayout.EnumPopup("attr id", attrs[i].efp);
                            attrs[i].val = EditorGUILayout.IntField("value", attrs[i].val);
                            attrs[i].unique_id = EditorGUILayout.IntField("unique_id", attrs[i].unique_id);
                            if (GUILayout.Button("delete"))
                            {
                                attrs.RemoveAt(i);
                                break;
                            }
                        }
                    }
                }

                {
                    // 额外属性
                    var attrs = currCfg.extra_attrs;
                    EditorGUILayout.LabelField("Extra Attributes");
                    if (GUILayout.Button("New"))
                    {
                        attrs.Add(new AttrKvStruct());
                    }
                    for (int i = 0; i < attrs.Count; ++i)
                    {
                        using (new EditorGUILayout.HorizontalScope())
                        {
                            attrs[i].efp = (NetProto.EFightParam)EditorGUILayout.EnumPopup("attr id", attrs[i].efp);
                            attrs[i].val = EditorGUILayout.IntField("value", attrs[i].val);
                            attrs[i].unique_id = EditorGUILayout.IntField("unique_id", attrs[i].unique_id);
                            if (GUILayout.Button("delete"))
                            {
                                attrs.RemoveAt(i);
                                break;
                            }
                        }
                    }
                }
            }
        }

        int AllowCalMinCfgId()
        {
            return (int)EffectType.Attrs * EffectEditorBase.EFFECT_CONFIG_ID_GAP;
        }

        int GetNextCfgId()
        {
            int maxId = 0;
            allCfgs.cfgs.ForEach((AttrsEffectConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            int allowMinCfgId = this.AllowCalMinCfgId();
            if (maxId < allowMinCfgId)
                maxId = allowMinCfgId;
            return maxId + 1;
        }

        public AttrsEffectConfig GetConfig(int id)
        {
            var ret = allCfgs.cfgs.Find((AttrsEffectConfig cfg) => { return cfg.id == id; });
            return ret;
        }
        public override EffectConfigBase GetCfg(int id)
        {
            return this.GetConfig(id);
        }
    }
}