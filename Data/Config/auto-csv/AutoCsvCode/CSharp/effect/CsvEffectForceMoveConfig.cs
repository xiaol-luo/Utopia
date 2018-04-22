using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectForceMoveConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_ignore_terrian = "ignore_terrian";
        public const string Field_Name_result = "result";
        public const string Field_Name_anchor = "anchor";
        public const string Field_Name_dir = "dir";
    }

    public class CsvEffectForceMoveConfig
    {
        public int id;
        public bool ignore_terrian;
        public string result = string.Empty;
        public string anchor = string.Empty;
        public float dir;

        public delegate bool ConfigCheckFunc(CsvEffectForceMoveConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectForceMoveConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectForceMoveConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectForceMoveConfig.Field_Name_ignore_terrian) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectForceMoveConfig.Field_Name_ignore_terrian], ref ignore_terrian);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectForceMoveConfig.Field_Name_result) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectForceMoveConfig.Field_Name_result], ref result);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectForceMoveConfig.Field_Name_anchor) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectForceMoveConfig.Field_Name_anchor], ref anchor);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectForceMoveConfig.Field_Name_dir) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectForceMoveConfig.Field_Name_dir], ref dir);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectForceMoveConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectForceMoveConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectForceMoveConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectForceMoveConfig> cfg_vec = new List<CsvEffectForceMoveConfig> ();
        public Dictionary<int, CsvEffectForceMoveConfig> id_to_key = new Dictionary<int, CsvEffectForceMoveConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectForceMoveConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectForceMoveConfig.Field_Name_ignore_terrian));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectForceMoveConfig.Field_Name_result));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectForceMoveConfig.Field_Name_anchor));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectForceMoveConfig.Field_Name_dir));
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
                    CsvEffectForceMoveConfig cfg = new CsvEffectForceMoveConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectForceMoveConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvEffectForceMoveConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectForceMoveConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}