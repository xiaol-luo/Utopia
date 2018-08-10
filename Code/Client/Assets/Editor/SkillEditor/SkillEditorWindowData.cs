
using Config;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public struct TopTabIdx
    {
        public const int SCENE = 0;
        public const int SCENE_UNIT = 1;
        public const int SKILL = 2;
        public const int EFFECT = 3;

        public const int COUNT = 4;
    }

    public class SkillEditorTabSetting
    {
        public int tabIdx;
        public string tabName;
        public System.Action logicImpl;
    }

    public partial class SkillEditorWindowData
    {
        public SkillEditorWindowData()
        {
            sceneTabData = new SceneTabData(this);
        }
        public const int WINDOW_FIX_WIDTH = 960;
        public const int WINDOW_MIN_HEIGHT = 640;

        public const string JSON_CONFIG_Path = "Res/Config/JsonConfig";
        public string jsonCfgPath
        {
            get
            {
                string ret = Path.Combine(Application.dataPath, JSON_CONFIG_Path);
                return ret;
            }
        }

        public int topToobardx = 0;
        public SkillEditorTabSetting[] tabSettings = null;

        public SceneTabData sceneTabData;
    }

    public class SceneTabData
    {
        public SceneTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
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
    }
}