using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvLogConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_alsoWritetoMe = "alsoWritetoMe";
        public const string Field_Name_logger_type = "logger_type";
        public const string Field_Name_name = "name";
        public const string Field_Name_log_level = "log_level";
        public const string Field_Name_save_file = "save_file";
        public const string Field_Name_rorating_max_size = "rorating_max_size";
        public const string Field_Name_rorating_max_files = "rorating_max_files";
        public const string Field_Name_daily_hour = "daily_hour";
        public const string Field_Name_daily_min = "daily_min";
    }

    public class CsvLogConfig
    {
        public int id;
        public List<int> alsoWritetoMe = new List<int>();
        public int logger_type;
        public string name = string.Empty;
        public int log_level;
        public string save_file = string.Empty;
        public int rorating_max_size;
        public int rorating_max_files;
        public int daily_hour;
        public int daily_min;

        public delegate bool ConfigCheckFunc(CsvLogConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_id], ref id);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_alsoWritetoMe) && ConfigUtil.Str2Vec (kvPairs[FieldName_CsvLogConfig.Field_Name_alsoWritetoMe], ref alsoWritetoMe);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_logger_type) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_logger_type], ref logger_type);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_name) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvLogConfig.Field_Name_name], ref name);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_log_level) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_log_level], ref log_level);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_save_file) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvLogConfig.Field_Name_save_file], ref save_file);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_rorating_max_size) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_rorating_max_size], ref rorating_max_size);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_rorating_max_files) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_rorating_max_files], ref rorating_max_files);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_daily_hour) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_daily_hour], ref daily_hour);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvLogConfig.Field_Name_daily_min) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvLogConfig.Field_Name_daily_min], ref daily_min);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvLogConfigSet
    {
        public string errMsg = string.Empty;

        public CsvLogConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvLogConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvLogConfig> cfg_vec = new List<CsvLogConfig> ();
        public Dictionary<int, CsvLogConfig> id_to_key = new Dictionary<int, CsvLogConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_alsoWritetoMe));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_logger_type));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_name));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_log_level));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_save_file));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_rorating_max_size));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_rorating_max_files));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_daily_hour));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvLogConfig.Field_Name_daily_min));
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
                    CsvLogConfig cfg = new CsvLogConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvLogConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvLogConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvLogConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}