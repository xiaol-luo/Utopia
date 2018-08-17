using Config;
using System;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public class ForceMoveEffectEditor : EffectEditorBase
    {
        public ForceMoveEffectEditor(EffectTabData _tabData) : base(_tabData)
        {
        }

        public const string CONFIG_PATH = "skill_editor/effect/force_move_effect.json";
        public string cfgPath
        {
            get
            {
                string ret = Path.Combine(tabData.editorData.jsonCfgPath, CONFIG_PATH);
                return ret;
            }
        }

        AllForceMoveEffectConfig _allCfgs = null;
        AllForceMoveEffectConfig allCfgs
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
            _allCfgs = JsonHelp.LoadStruct<AllForceMoveEffectConfig>(cfgPath);
        }

        public override bool SaveCfgs()
        {
            var toSave = (null != _allCfgs ? _allCfgs : new AllForceMoveEffectConfig());
            bool ret = JsonHelp.SaveStruct(cfgPath, toSave);
            return ret;
        }

        public override ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = new ConfigIdNameListStruct();
            allCfgs.cfgs.ForEach((ForceMoveEffectConfig cfg) => { ret.ids.Add(cfg.id); ret.names.Add(cfg.name); });
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
                    var newCfg = new Config.ForceMoveEffectConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("force_move_effect_{0}", nextCfgId)
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
                currCfg.ignore_terrian = SkillEditorWindow.BoolPopup("ignore terrian", currCfg.ignore_terrian);

                using (new EditorGUILayout.HorizontalScope())
                {
                    currCfg.move_setting = (MoveSetting)EditorGUILayout.EnumPopup("move setting", currCfg.move_setting);
                    switch (currCfg.move_setting)
                    {
                        case MoveSetting.TimeSpeed:
                            {
                                currCfg.move_sec = EditorGUILayout.FloatField("move sec", currCfg.move_sec);
                                currCfg.move_speed = EditorGUILayout.FloatField("move speed", currCfg.move_speed);
                            }
                            break;
                        case MoveSetting.TimeDistance:
                            {
                                currCfg.move_sec = EditorGUILayout.FloatField("move sec", currCfg.move_sec);
                                currCfg.move_distance = EditorGUILayout.FloatField("move distance", currCfg.move_distance);
                            }
                            break;
                        case MoveSetting.DistanceSpeed:
                            {
                                currCfg.move_distance = EditorGUILayout.FloatField("move distance", currCfg.move_distance);
                                currCfg.move_speed = EditorGUILayout.FloatField("move speed", currCfg.move_speed);
                            }
                            break;
                    }
                }

                currCfg.anchor = (EEffectFilterAnchor)EditorGUILayout.EnumPopup("anchor", currCfg.anchor);
                currCfg.angle = EditorGUILayout.FloatField("angle", currCfg.angle);
            }
        }

        int AllowCalMinCfgId()
        {
            return (int)EffectType.ForceMove * EffectEditorBase.EFFECT_CONFIG_ID_GAP;
        }

        int GetNextCfgId()
        {
            int maxId = 0;
            allCfgs.cfgs.ForEach((ForceMoveEffectConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            int allowMinCfgId = this.AllowCalMinCfgId();
            if (maxId < allowMinCfgId)
                maxId = allowMinCfgId;
            return maxId + 1;
        }

        public ForceMoveEffectConfig GetConfig(int id)
        {
            var ret = allCfgs.cfgs.Find((ForceMoveEffectConfig cfg) => { return cfg.id == id; });
            return ret;
        }
        public override EffectConfigBase GetCfg(int id)
        {
            return this.GetConfig(id);
        }
    }
}