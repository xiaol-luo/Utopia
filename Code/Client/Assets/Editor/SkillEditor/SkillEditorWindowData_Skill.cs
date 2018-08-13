
using Config;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public class SkillTabData
    {
        public SkillTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
        }

        SkillEditorWindowData editorData;
        public const string SKILL_CONFIG_PATH = "skill_editor/skill_config.json";
        public string skillCfgPath {
            get
            {
                string ret = Path.Combine(editorData.jsonCfgPath, SKILL_CONFIG_PATH);
                return ret;
            }
        }

        public int selectedSkillCfgId = 0;
        public int selectedSkillLvlIdx = 0;
        AllSkillConfig _skillCfgs = null;
        public AllSkillConfig skillConfigs
        {
            get
            {
                if (null == _skillCfgs)
                {
                    this.LoadSkillConfigs();
                }
                return _skillCfgs;
            }
            set
            {
                _skillCfgs = value;
            }
        }

        public void LoadSkillConfigs()
        {
            _skillCfgs = JsonHelp.LoadStruct<AllSkillConfig>(skillCfgPath);
        }

        public bool SaveSkillConfigs()
        {
            var toSave = (null != _skillCfgs ? _skillCfgs : new AllSkillConfig());
            bool ret = JsonHelp.SaveStruct(skillCfgPath, toSave);
            return ret;
        }

        public List<string> GetSkillNames()
        {
            List<string> ret = new List<string>();
            skillConfigs.cfgs.ForEach((SkillConfig cfg) => { ret.Add(string.Format("{0}:{1}", cfg.id, cfg.name)); });
            return ret;
        }
        public List<int> GetSkillIds()
        {
            List<int> ret = new List<int>();
            skillConfigs.cfgs.ForEach((SkillConfig cfg) => { ret.Add(cfg.id); });
            return ret;
        }

        public int GetNextSkillCfgId()
        {
            int maxId = 0;
            skillConfigs.cfgs.ForEach((SkillConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            return maxId + 1;
        }
        public SkillConfig GetSkillConfig(int id)
        {
            SkillConfig ret = skillConfigs.cfgs.Find((SkillConfig cfg) => { return cfg.id == id; });
            return ret;
        }
    }
}