using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectGroupConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_base_attrs = "base_attrs";
        public const string Field_Name_extra_attrs = "extra_attrs";
        public const string Field_Name_percent_attrs = "percent_attrs";
        public const string Field_Name_need_guide = "need_guide";
        public const string Field_Name_can_cancel_guide = "can_cancel_guide";
    }

    public class CsvEffectGroupConfig
    {
        public int id;
        public List<int> base_attrs = new List<int>();
        public List<List<int>> extra_attrs = new List<List<int>>();
        public List<List<int>> percent_attrs = new List<List<int>>();
        public int need_guide;
        public int can_cancel_guide;

        public delegate bool ConfigCheckFunc(CsvEffectGroupConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectGroupConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectGroupConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectGroupConfig.Field_Name_base_attrs) && ConfigUtil.Str2Vec (kvPairs[FieldName_CsvEffectGroupConfig.Field_Name_base_attrs], ref base_attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectGroupConfig.Field_Name_extra_attrs) && ConfigUtil.Str2VecVec (kvPairs[FieldName_CsvEffectGroupConfig.Field_Name_extra_attrs], ref extra_attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectGroupConfig.Field_Name_percent_attrs) && ConfigUtil.Str2VecVec (kvPairs[FieldName_CsvEffectGroupConfig.Field_Name_percent_attrs], ref percent_attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectGroupConfig.Field_Name_need_guide) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectGroupConfig.Field_Name_need_guide], ref need_guide);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectGroupConfig.Field_Name_can_cancel_guide) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectGroupConfig.Field_Name_can_cancel_guide], ref can_cancel_guide);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectGroupConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectGroupConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectGroupConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectGroupConfig> cfg_vec = new List<CsvEffectGroupConfig> ();
        public Dictionary<int, CsvEffectGroupConfig> id_to_key = new Dictionary<int, CsvEffectGroupConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectGroupConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectGroupConfig.Field_Name_base_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectGroupConfig.Field_Name_extra_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectGroupConfig.Field_Name_percent_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectGroupConfig.Field_Name_need_guide));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectGroupConfig.Field_Name_can_cancel_guide));
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
                    CsvEffectGroupConfig cfg = new CsvEffectGroupConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectGroupConfig Init Fail, row {0}", csv.CurrentRecordIndex);
                        return false;
                    }
                    cfg_vec.Add(cfg);
                }
            }

            foreach (var cfg in cfg_vec)
            {
                {
                    if (id_to_key.ContainsKey(cfg.id))
                    {
                        errMsg = string.Format("CsvEffectGroupConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectGroupConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}