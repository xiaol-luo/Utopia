
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
        public const int FILTER = 3;
        public const int EFFECT = 4;

        public const int COUNT = 5;
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
            suTabData = new SceneUnitTabData(this);
            skillTabData = new SkillTabData(this);
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
        public SceneUnitTabData suTabData;
        public SkillTabData skillTabData;

        public void LoadAllCfg()
        {
            sceneTabData.LoadSceneConfigs();
            suTabData.LoadSceneUnitConfigs();
            skillTabData.LoadSkillConfigs();
        }
        public void SaveAllCfg()
        {
            sceneTabData.SaveSceneConfigs();
            suTabData.SaveSceneUnitConfigs();
            skillTabData.SaveSkillConfigs();
        }
    }
}