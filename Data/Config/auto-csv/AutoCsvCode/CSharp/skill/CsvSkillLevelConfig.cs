using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvSkillLevelConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_level = "level";
        public const string Field_Name_preparing_span = "preparing_span";
        public const string Field_Name_releasing_span = "releasing_span";
        public const string Field_Name_lasting_span = "lasting_span";
        public const string Field_Name_comsume_mp = "comsume_mp";
        public const string Field_Name_cd = "cd";
        public const string Field_Name_cast_distance = "cast_distance";
        public const string Field_Name_can_move = "can_move";
    }

    public class CsvSkillLevelConfig
    {
        public int id;
        public int level;
        public int preparing_span;
        public int releasing_span;
        public int lasting_span;
        public int comsume_mp;
        public int cd;
        public float cast_distance;
        public bool can_move;

        public delegate bool ConfigCheckFunc(CsvSkillLevelConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_level) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_level], ref level);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_preparing_span) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_preparing_span], ref preparing_span);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_releasing_span) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_releasing_span], ref releasing_span);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_lasting_span) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_lasting_span], ref lasting_span);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_comsume_mp) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_comsume_mp], ref comsume_mp);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_cd) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_cd], ref cd);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_cast_distance) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_cast_distance], ref cast_distance);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSkillLevelConfig.Field_Name_can_move) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSkillLevelConfig.Field_Name_can_move], ref can_move);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvSkillLevelConfigSet
    {
        public string errMsg = string.Empty;

        public CsvSkillLevelConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvSkillLevelConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvSkillLevelConfig> cfg_vec = new List<CsvSkillLevelConfig> ();
        public Dictionary<int, List<CsvSkillLevelConfig>> id_to_group = new Dictionary<int, List<CsvSkillLevelConfig>>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_level));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_preparing_span));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_releasing_span));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_lasting_span));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_comsume_mp));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_cd));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_cast_distance));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSkillLevelConfig.Field_Name_can_move));
                }
                catch (Exception e)
                {
                    errMsg = e.Message;
                    return false;
                }
                csv.ReadNextRecord();
                while (csv.ReadNextRecord())
                {
                    Dictionary<string, string> kvPairs = new Dictionary<string, string>();
                    foreach (int fieldIdx in fieldIdxList)
                    {
                        kvPairs[headers[fieldIdx]] = csv[fieldIdx];
                        
                    }
                    if (string.IsNullOrWhiteSpace(kvPairs[headers[0]]))
                        continue;
                    CsvSkillLevelConfig cfg = new CsvSkillLevelConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvSkillLevelConfig Init Fail, row {0}", csv.CurrentRecordIndex);
                        return false;
                    }
                    cfg_vec.Add(cfg);
                }
            }

            foreach (var cfg in cfg_vec)
            {
                {
                    List<CsvSkillLevelConfig> vec = null;
                    if (!id_to_group.TryGetValue(cfg.id, out vec))
                    {
                        vec = new List<CsvSkillLevelConfig>();
                        id_to_group[cfg.id] = vec;
                    }
                    vec.Add(cfg);
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvSkillLevelConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}