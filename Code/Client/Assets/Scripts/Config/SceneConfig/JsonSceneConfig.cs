
using System.Collections.Generic;
using UnityEngine;

namespace Config
{
    public class AllSceneConfig
    {
        public Dictionary<string, SceneConfig> cfgs = new Dictionary<string, SceneConfig>();
    }

    public class AllSceneUnitConfig
    {
        public Dictionary<int, SceneUnitConfig> cfgs = new Dictionary<int, SceneUnitConfig>();
    }

    public class AllSuFilterConfig
    {
        public Dictionary<int, SuFilterConfig> cfgs = new Dictionary<int, SuFilterConfig>();
    }

    public class AllSkillConfig
    {
        public Dictionary<int, SkillConfig> cfgs = new Dictionary<int, SkillConfig>();
    }

    public class AllAttrsEffectConfig
    {
        public Dictionary<int, AllAttrsEffectConfig> cfgs = new Dictionary<int, AllAttrsEffectConfig>();
    }

    public class AllEffectGroupConfig
    {
        public Dictionary<int, EffectGroupConfig> cfgs = new Dictionary<int, EffectGroupConfig>();
    }

    public class AllEffectScriptConfig
    {
        public Dictionary<int, EffectScriptConfig> cfgs = new Dictionary<int, EffectScriptConfig>();
    }

    public class AllEffectSearcherConfig
    {
        public Dictionary<int, EffectSearcherConfig> cfgs = new Dictionary<int, EffectSearcherConfig>();
    }

    public class AllForceMoveEffectConfig
    {
        public Dictionary<int, ForceMoveEffectConfig> cfgs = new Dictionary<int, ForceMoveEffectConfig>();
    }
    
    public class AllHealEffectConfig
    {
        public Dictionary<int, HealEffectConfig> cfgs = new Dictionary<int, HealEffectConfig>();
    }

    public class AllHurtEffectConfig
    {
        public Dictionary<int, HurtEffectConfig> cfgs = new Dictionary<int, HurtEffectConfig>();
    }
}
