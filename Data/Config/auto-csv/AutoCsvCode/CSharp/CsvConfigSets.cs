using System;
using System.IO;

namespace Config
{
    public class CsvConfigSets
    {
        public string errMsg = string.Empty;
        public CsvLogConfigSet csv_CsvLogConfigSet = new CsvLogConfigSet();
        public CsvSceneConfigSet csv_CsvSceneConfigSet = new CsvSceneConfigSet();
        public CsvSkillConfigSet csv_CsvSkillConfigSet = new CsvSkillConfigSet();
        public CsvSkillLevelConfigSet csv_CsvSkillLevelConfigSet = new CsvSkillLevelConfigSet();
        public CsvEffectHurtConfigSet csv_CsvEffectHurtConfigSet = new CsvEffectHurtConfigSet();
        public CsvEffectHealConfigSet csv_CsvEffectHealConfigSet = new CsvEffectHealConfigSet();
        public CsvEffectAttrsConfigSet csv_CsvEffectAttrsConfigSet = new CsvEffectAttrsConfigSet();
        public CsvEffectFilterConfigSet csv_CsvEffectFilterConfigSet = new CsvEffectFilterConfigSet();
        public CsvEffectGroupConfigSet csv_CsvEffectGroupConfigSet = new CsvEffectGroupConfigSet();
        public CsvEffectScriptConfigSet csv_CsvEffectScriptConfigSet = new CsvEffectScriptConfigSet();
        public CsvEffectForceMoveConfigSet csv_CsvEffectForceMoveConfigSet = new CsvEffectForceMoveConfigSet();
        public CsvEffectSearcherConfigSet csv_CsvEffectSearcherConfigSet = new CsvEffectSearcherConfigSet();

        public bool Load(string root_path)
        {
            if (!csv_CsvLogConfigSet.Load(Path.Combine(root_path, "Log/CsvLogConfig.csv")))
            {
                errMsg = "Load csv_CsvLogConfigSet fail";
                return false;
            }
            if (!csv_CsvSceneConfigSet.Load(Path.Combine(root_path, "scene/CsvSceneConfig.csv")))
            {
                errMsg = "Load csv_CsvSceneConfigSet fail";
                return false;
            }
            if (!csv_CsvSkillConfigSet.Load(Path.Combine(root_path, "skill/CsvSkillConfig.csv")))
            {
                errMsg = "Load csv_CsvSkillConfigSet fail";
                return false;
            }
            if (!csv_CsvSkillLevelConfigSet.Load(Path.Combine(root_path, "skill/CsvSkillLevelConfig.csv")))
            {
                errMsg = "Load csv_CsvSkillLevelConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectHurtConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectHurtConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectHurtConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectHealConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectHealConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectHealConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectAttrsConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectAttrsConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectAttrsConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectFilterConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectFilterConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectFilterConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectGroupConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectGroupConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectGroupConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectScriptConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectScriptConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectScriptConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectForceMoveConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectForceMoveConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectForceMoveConfigSet fail";
                return false;
            }
            if (!csv_CsvEffectSearcherConfigSet.Load(Path.Combine(root_path, "effect/CsvEffectSearcherConfig.csv")))
            {
                errMsg = "Load csv_CsvEffectSearcherConfigSet fail";
                return false;
            }

            return true;
        }
    }
}