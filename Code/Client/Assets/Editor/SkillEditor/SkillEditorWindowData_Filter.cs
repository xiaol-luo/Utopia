
using Config;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public class SuFilterTabData
    {
        public SuFilterTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
        }

        SkillEditorWindowData editorData;
        public const string CONFIG_PATH = "skill_editor/filter_config.json";
        public string cfgPath {
            get
            {
                string ret = Path.Combine(editorData.jsonCfgPath, CONFIG_PATH);
                return ret;
            }
        }

        public int selectedCfgId = 0;
        AllSuFilterConfig _allCfgs = null;
        public AllSuFilterConfig allCfgs
        {
            get
            {
                if (null == _allCfgs)
                {
                    this.LoadConfigs();
                }
                return _allCfgs;
            }
            set
            {
                _allCfgs = value;
            }
        }

        public void LoadConfigs()
        {
            _allCfgs = JsonHelp.LoadStruct<AllSuFilterConfig>(cfgPath);
        }

        public bool SaveConfigs()
        {
            var toSave = (null != _allCfgs ? _allCfgs : new AllSuFilterConfig());
            bool ret = JsonHelp.SaveStruct(cfgPath, toSave);
            return ret;
        }

        public List<string> GetCfgNames()
        {
            List<string> ret = new List<string>();
            allCfgs.cfgs.ForEach((SuFilterConfig cfg) => { ret.Add(string.Format("{0}:{1}", cfg.id, cfg.name)); });
            return ret;
        }
        public List<int> GetCfgIds()
        {
            List<int> ret = new List<int>();
            allCfgs.cfgs.ForEach((SuFilterConfig cfg) => { ret.Add(cfg.id); });
            return ret;
        }

        public int GetNextCfgId()
        {
            int maxId = 0;
            allCfgs.cfgs.ForEach((SuFilterConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            return maxId + 1;
        }
        public SuFilterConfig GetConfig(int id)
        {
            var ret = allCfgs.cfgs.Find((SuFilterConfig cfg) => { return cfg.id == id; });
            return ret;
        }
    }
}