using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectSearcherConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_filter_id = "filter_id";
        public const string Field_Name_effect_ids = "effect_ids";
    }

    public class CsvEffectSearcherConfig
    {
        public int id;
        public int filter_id;
        public List<int> effect_ids = new List<int>();

        public delegate bool ConfigCheckFunc(CsvEffectSearcherConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectSearcherConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectSearcherConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectSearcherConfig.Field_Name_filter_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectSearcherConfig.Field_Name_filter_id], ref filter_id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectSearcherConfig.Field_Name_effect_ids) && ConfigUtil.Str2Vec (kvPairs[FieldName_CsvEffectSearcherConfig.Field_Name_effect_ids], ref effect_ids);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectSearcherConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectSearcherConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectSearcherConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectSearcherConfig> cfg_vec = new List<CsvEffectSearcherConfig> ();
        public Dictionary<int, CsvEffectSearcherConfig> id_to_key = new Dictionary<int, CsvEffectSearcherConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectSearcherConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectSearcherConfig.Field_Name_filter_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectSearcherConfig.Field_Name_effect_ids));
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
                    CsvEffectSearcherConfig cfg = new CsvEffectSearcherConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectSearcherConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvEffectSearcherConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectSearcherConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}