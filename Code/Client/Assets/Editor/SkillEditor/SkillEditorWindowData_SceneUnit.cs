
using Config;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public class SceneUnitTabData
    {
        public SceneUnitTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
        }

        SkillEditorWindowData editorData;
        public const string SCENE_UNIT_CONFIG_PATH = "skill_editor/scene_unit_config.json";
        public string sceneUnitCfgPath {
            get
            {
                string ret = Path.Combine(editorData.jsonCfgPath, SCENE_UNIT_CONFIG_PATH);
                return ret;
            }
        }

        public int selectedSuCfgId = 0;
        AllSceneUnitConfig _suCfgs = null;
        public AllSceneUnitConfig suConfig
        {
            get
            {
                if (null == _suCfgs)
                {
                    this.LoadSceneUnitConfigs();
                }
                return _suCfgs;
            }
            set
            {
                _suCfgs = value;
            }
        }

        public void LoadSceneUnitConfigs()
        {
            _suCfgs = JsonHelp.LoadStruct<AllSceneUnitConfig>(sceneUnitCfgPath);
        }

        public bool SaveSceneUnitConfigs()
        {
            var toSave = (null != _suCfgs ? _suCfgs : new AllSceneUnitConfig());
            bool ret = JsonHelp.SaveStruct(sceneUnitCfgPath, toSave);
            return ret;
        }

        public List<string> GetSuNames()
        {
            List<string> ret = new List<string>();
            suConfig.cfgs.ForEach((SceneUnitConfig cfg) => { ret.Add(string.Format("{0}:{1}", cfg.id, cfg.name)); });
            return ret;
        }
        public List<int> GetSuIds()
        {
            List<int> ret = new List<int>();
            suConfig.cfgs.ForEach((SceneUnitConfig cfg) => { ret.Add(cfg.id); });
            return ret;
        }

        public int GetNextSuCfgId()
        {
            int maxId = 0;
            suConfig.cfgs.ForEach((SceneUnitConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            return maxId + 1;
        }
        public SceneUnitConfig GetSuConfig(int id)
        {
            SceneUnitConfig ret = suConfig.cfgs.Find((SceneUnitConfig cfg) => { return cfg.id == id; });
            return ret;
        }
    }
}