
using Config;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public class SceneTabData
    {
        public SceneTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
            selecteds = new Selecteds(this);
        }

        SkillEditorWindowData editorData;
        public const string SCENE_CONFIG_PATH = "skill_editor/scene_config.json";
        public string sceneCfgPath {
            get
            {
                string ret = Path.Combine(editorData.jsonCfgPath, SCENE_CONFIG_PATH);
                return ret;
            }
        }
        
        AllSceneConfig _sceneCfgs = null;
        public AllSceneConfig sceneConfig
        {
            get
            {
                if (null == _sceneCfgs)
                {
                    this.LoadSceneConfigs();
                }
                return _sceneCfgs;
            }
            set
            {
                _sceneCfgs = value;
            }
        }

        public void LoadSceneConfigs()
        {
            _sceneCfgs = JsonHelp.LoadStruct<AllSceneConfig>(sceneCfgPath);
        }

        public bool SaveSceneConfigs()
        {
            var toSave = (null != _sceneCfgs ? _sceneCfgs : new AllSceneConfig());
            bool ret = JsonHelp.SaveStruct(sceneCfgPath, toSave);
            return ret;
        }

        public SceneConfig GetSceneConfig(int sceneId)
        {
            SceneConfig ret = sceneConfig.cfgs.Find((SceneConfig cfg) => { return cfg.id == sceneId; });
            return ret;
        }

        public int GetNextSceneId()
        {
            int maxId = 0;
            sceneConfig.cfgs.ForEach((SceneConfig cfg) => { if (maxId < cfg.id) maxId = cfg.id; });
            return maxId + 1;
        }

        public List<string> GetSceneNames()
        {
            List<string> ret = new List<string>();
            sceneConfig.cfgs.ForEach((SceneConfig cfg) => {
                string name = string.Format("{0}:{1}", cfg.id, cfg.name);
                ret.Add(name);
            });
            return ret;
        }
        public List<int> GetSceneIds()
        {
            List<int> ret = new List<int>();
            sceneConfig.cfgs.ForEach((SceneConfig cfg) => { ret.Add(cfg.id); });
            return ret;
        }


        public class Selecteds
        {
            public Selecteds(SceneTabData _tabData)
            {
                tabData = _tabData;
            }

            SceneTabData tabData;
            public int sceneId;
        }
        public Selecteds selecteds;
    }
}