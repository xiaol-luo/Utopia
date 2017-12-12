using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectAttrsConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_attrs = "attrs";
        public const string Field_Name_reversible = "reversible";
        public const string Field_Name_last_time = "last_time";
    }

    public class CsvEffectAttrsConfig
    {
        public int id;
        public Dictionary<int, int> attrs = new Dictionary<int, int>();
        public bool reversible;
        public int last_time;

        public delegate bool ConfigCheckFunc(CsvEffectAttrsConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_attrs) && ConfigUtil.Str2Map (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_attrs], ref attrs);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_reversible) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_reversible], ref reversible);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectAttrsConfig.Field_Name_last_time) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectAttrsConfig.Field_Name_last_time], ref last_time);
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
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_attrs));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_reversible));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectAttrsConfig.Field_Name_last_time));
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