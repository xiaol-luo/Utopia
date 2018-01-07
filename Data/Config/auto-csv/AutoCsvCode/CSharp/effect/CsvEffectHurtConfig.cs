using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectHurtConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_value = "value";
    }

    public class CsvEffectHurtConfig
    {
        public int id;
        public int value;

        public delegate bool ConfigCheckFunc(CsvEffectHurtConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectHurtConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectHurtConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectHurtConfig.Field_Name_value) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectHurtConfig.Field_Name_value], ref value);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectHurtConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectHurtConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectHurtConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectHurtConfig> cfg_vec = new List<CsvEffectHurtConfig> ();
        public Dictionary<int, CsvEffectHurtConfig> id_to_key = new Dictionary<int, CsvEffectHurtConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectHurtConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectHurtConfig.Field_Name_value));
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
                    CsvEffectHurtConfig cfg = new CsvEffectHurtConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectHurtConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvEffectHurtConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectHurtConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}