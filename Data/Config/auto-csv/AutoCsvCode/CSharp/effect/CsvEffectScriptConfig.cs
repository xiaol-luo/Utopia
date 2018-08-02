using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectScriptConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_class_name = "class_name";
        public const string Field_Name_str_param = "str_param";
        public const string Field_Name_json_param = "json_param";
        public const string Field_Name_int_param = "int_param";
    }

    public class CsvEffectScriptConfig
    {
        public int id;
        public string class_name = string.Empty;
        public string str_param = string.Empty;
        public string json_param = string.Empty;
        public int int_param;

        public delegate bool ConfigCheckFunc(CsvEffectScriptConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectScriptConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectScriptConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectScriptConfig.Field_Name_class_name) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectScriptConfig.Field_Name_class_name], ref class_name);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectScriptConfig.Field_Name_str_param) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectScriptConfig.Field_Name_str_param], ref str_param);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectScriptConfig.Field_Name_json_param) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectScriptConfig.Field_Name_json_param], ref json_param);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectScriptConfig.Field_Name_int_param) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectScriptConfig.Field_Name_int_param], ref int_param);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectScriptConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectScriptConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectScriptConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectScriptConfig> cfg_vec = new List<CsvEffectScriptConfig> ();
        public Dictionary<int, CsvEffectScriptConfig> id_to_key = new Dictionary<int, CsvEffectScriptConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectScriptConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectScriptConfig.Field_Name_class_name));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectScriptConfig.Field_Name_str_param));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectScriptConfig.Field_Name_json_param));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectScriptConfig.Field_Name_int_param));
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
                    CsvEffectScriptConfig cfg = new CsvEffectScriptConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectScriptConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvEffectScriptConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectScriptConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}