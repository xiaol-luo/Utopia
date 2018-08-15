
using Config;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public class EffectGroupTabData
    {
        public EffectGroupTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
        }

        SkillEditorWindowData editorData;
        public const string EFFECT_GROUP_CONFIG_PATH = "skill_editor/effect/effect_group_config.json";
        public string effectGroupCfgPath {
            get
            {
                string ret = Path.Combine(editorData.jsonCfgPath, EFFECT_GROUP_CONFIG_PATH);
                return ret;
            }
        }

        public int selectedEffectGroupCfgId = 0;
        AllEffectGroupConfig _effectGroupCfg = null;
        public AllEffectGroupConfig effectGroupConfig
        {
            get
            {
                if (null == _effectGroupCfg)
                {
                    this.LoadEffectGroupConfigs();
                }
                return _effectGroupCfg;
            }
            set
            {
                _effectGroupCfg = value;
            }
        }

        public void LoadEffectGroupConfigs()
        {
            _effectGroupCfg = JsonHelp.LoadStruct<AllEffectGroupConfig>(effectGroupCfgPath);
        }

        public bool SaveSceneUnitConfigs()
        {
            var toSave = (null != _effectGroupCfg ? _effectGroupCfg : new AllEffectGroupConfig());
            bool ret = JsonHelp.SaveStruct(effectGroupCfgPath, toSave);
            return ret;
        }

        public List<string> GetEffectGroupNames()
        {
            List<string> ret = new List<string>();
            effectGroupConfig.cfgs.ForEach((EffectGroupConfig cfg) => { ret.Add(string.Format("{0}:{1}", cfg.id, cfg.name)); });
            return ret;
        }
        public List<int> GetEffectGroupIds()
        {
            List<int> ret = new List<int>();
            effectGroupConfig.cfgs.ForEach((EffectGroupConfig cfg) => { ret.Add(cfg.id); });
            return ret;
        }

        public int GetNextEffectGroupCfgId()
        {
            int maxId = 0;
            effectGroupConfig.cfgs.ForEach((EffectGroupConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            return maxId + 1;
        }
        public EffectGroupConfig GetEffectGroupConfig(int id)
        {
            var ret = effectGroupConfig.cfgs.Find((EffectGroupConfig cfg) => { return cfg.id == id; });
            return ret;
        }
    }
}