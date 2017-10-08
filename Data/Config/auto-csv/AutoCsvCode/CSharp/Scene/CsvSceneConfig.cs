using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvSceneConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_terrain_file_path = "terrain_file_path";
    }

    public class CsvSceneConfig
    {
        public int id;
        public string terrain_file_path = string.Empty;

        public delegate bool ConfigCheckFunc(CsvSceneConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSceneConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvSceneConfig.Field_Name_id], ref id);
        all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvSceneConfig.Field_Name_terrain_file_path) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvSceneConfig.Field_Name_terrain_file_path], ref terrain_file_path);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvSceneConfigSet
    {
        public string errMsg = string.Empty;

        public CsvSceneConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvSceneConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvSceneConfig> cfg_vec = new List<CsvSceneConfig> ();
        public Dictionary<int, CsvSceneConfig> id_to_key = new Dictionary<int, CsvSceneConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSceneConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvSceneConfig.Field_Name_terrain_file_path));
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
                    CsvSceneConfig cfg = new CsvSceneConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvSceneConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvSceneConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvSceneConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}