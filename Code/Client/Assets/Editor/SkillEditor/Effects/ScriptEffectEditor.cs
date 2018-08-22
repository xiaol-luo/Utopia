using Config;
using System;
using System.Collections.Generic;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class ScriptEffectEditor : EffectEditorBase
    {
        Dictionary<EEffectScriptType, System.Action<EffectScriptConfig, SkillEditorWindowData>> m_impleEditorDetailLogic = new Dictionary<EEffectScriptType, Action<EffectScriptConfig, SkillEditorWindowData>>();
        public ScriptEffectEditor(EffectTabData _tabData) : base(_tabData)
        {
            m_impleEditorDetailLogic[EEffectScriptType.Bullet] = ImplBulletEditorLogic;
        }

        public const string CONFIG_PATH = "skill_editor/effect/script_effect.json";
        public string cfgPath
        {
            get
            {
                string ret = Path.Combine(tabData.editorData.jsonCfgPath, CONFIG_PATH);
                return ret;
            }
        }

        AllEffectScriptConfig _allCfgs = null;
        AllEffectScriptConfig allCfgs
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
            _allCfgs = JsonHelp.LoadStruct<AllEffectScriptConfig>(cfgPath);
        }

        public override bool SaveCfgs()
        {
            var toSave = (null != _allCfgs ? _allCfgs : new AllEffectScriptConfig());
            bool ret = JsonHelp.SaveStruct(cfgPath, toSave);
            return ret;
        }

        public override ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = new ConfigIdNameListStruct();
            allCfgs.cfgs.ForEach((EffectScriptConfig cfg) => { ret.ids.Add(cfg.id); ret.names.Add(cfg.name); });
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
                    var newCfg = new Config.EffectScriptConfig()
                    {
                        id = nextCfgId,
                        name = string.Format("script_effect_{0}", nextCfgId)
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
                selectedCfgId = currCfg.id;
                currCfg.name = EditorGUILayout.TextField("name", currCfg.name);
                currCfg.script_type = (EEffectScriptType)EditorGUILayout.EnumPopup("script type", currCfg.script_type);
                currCfg.class_name = EditorGUILayout.TextField("class name", EffectScriptSetting.s_typeLuaClassMap[currCfg.script_type]);
                var implFn = m_impleEditorDetailLogic[currCfg.script_type];
                implFn(currCfg, tabData.editorData);
            }
        }

        int AllowCalMinCfgId()
        {
            return (int)EffectType.Script * EffectEditorBase.EFFECT_CONFIG_ID_GAP;
        }

        int GetNextCfgId()
        {
            int maxId = 0;
            allCfgs.cfgs.ForEach((EffectScriptConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            int allowMinCfgId = this.AllowCalMinCfgId();
            if (maxId < allowMinCfgId)
                maxId = allowMinCfgId;
            return maxId + 1;
        }

        public EffectScriptConfig GetConfig(int id)
        {
            var ret = allCfgs.cfgs.Find((EffectScriptConfig cfg) => { return cfg.id == id; });
            return ret;
        }
        public override EffectConfigBase GetCfg(int id)
        {
            return this.GetConfig(id);
        }
    }
}