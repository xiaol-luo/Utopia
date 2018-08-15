
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
        public const int EFFECT_GROUP = 4;
        public const int EFFECT = 5;

        public const int COUNT = 6;
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
            effectGroupTabData = new EffectGroupTabData(this);
            filterTabData = new SuFilterTabData(this);
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
        public EffectGroupTabData effectGroupTabData;
        public SuFilterTabData filterTabData;

        public void LoadAllCfg()
        {
            sceneTabData.LoadSceneConfigs();
            suTabData.LoadSceneUnitConfigs();
            skillTabData.LoadSkillConfigs();
            effectGroupTabData.LoadEffectGroupConfigs();
            filterTabData.LoadConfigs();
        }
        public void SaveAllCfg()
        {
            sceneTabData.SaveSceneConfigs();
            suTabData.SaveSceneUnitConfigs();
            skillTabData.SaveSkillConfigs();
            effectGroupTabData.SaveSceneUnitConfigs();
            filterTabData.SaveConfigs();
        }
    }
}