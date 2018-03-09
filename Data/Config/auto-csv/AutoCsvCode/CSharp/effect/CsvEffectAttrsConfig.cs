using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectAttrsConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_base_attrs = "base_attrs";
        public const string Field_Name_extra_attrs = "extra_attrs";
        public const string Field_Name_percent_attrs = "percent_attrs";
        public const string Field_Name_hold_time_ms = "hold_time_ms";
        public const string Field_Name_unique_id = "unique_id";
    }

    public class CsvEffectAttrsConfig
    {
        public int id;
        public List<List<int>> base_attrs = new List<List<int>>();
        public List<List<int>> extra_attrs = new List<List<int>>();
        public List<List<int>> percent_attrs = new List<List<int>>();
        public int hold_time_ms;
        public int unique_id;

        public delegate bool ConfigCheckFunc(CsvEffectAttrsConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_base_attrs) && ConfigUtil.Str2VecVec (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_base_attrs], ref base_attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_extra_attrs) && ConfigUtil.Str2VecVec (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_extra_attrs], ref extra_attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_percent_attrs) && ConfigUtil.Str2VecVec (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_percent_attrs], ref percent_attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_hold_time_ms) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_hold_time_ms], ref hold_time_ms);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_unique_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_unique_id], ref unique_id);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectAttrsConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectAttrsConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectAttrsConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectAttrsConfig> cfg_vec = new List<CsvEffectAttrsConfig> ();
        public Dictionary<int, CsvEffectAttrsConfig> id_to_key = new Dictionary<int, CsvEffectAttrsConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_base_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_extra_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_percent_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_hold_time_ms));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_unique_id));
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
                    CsvEffectAttrsConfig cfg = new CsvEffectAttrsConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectAttrsConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvEffectAttrsConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectAttrsConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}