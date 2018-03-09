using System;
using System.Collections.Generic;
using LumenWorks.Framework.IO.Csv;
using System.IO;

namespace Config
{
    internal class FieldName_CsvEffectFilterConfig
    {
        public const string Field_Name_id = "id";
        public const string Field_Name_limit_num = "limit_num";
        public const string Field_Name_limit_num_priority = "limit_num_priority";
        public const string Field_Name_unit_types = "unit_types";
        public const string Field_Name_relations = "relations";
        public const string Field_Name_anchor = "anchor";
        public const string Field_Name_shape_circle = "shape_circle";
        public const string Field_Name_shape_rect = "shape_rect";
        public const string Field_Name_shape_sector = "shape_sector";
    }

    public class CsvEffectFilterConfig
    {
        public int id;
        public int limit_num;
        public string limit_num_priority = string.Empty;
        public string unit_types = string.Empty;
        public string relations = string.Empty;
        public string anchor = string.Empty;
        public int shape_circle;
        public List<int> shape_rect = new List<int>();
        public List<int> shape_sector = new List<int>();

        public delegate bool ConfigCheckFunc(CsvEffectFilterConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            bool all_ok = true;
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_id) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_id], ref id);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_limit_num) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_limit_num], ref limit_num);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_limit_num_priority) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_limit_num_priority], ref limit_num_priority);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_unit_types) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_unit_types], ref unit_types);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_relations) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_relations], ref relations);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_anchor) && ConfigUtil.Str2Str (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_anchor], ref anchor);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_shape_circle) && ConfigUtil.Str2BaseValue (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_shape_circle], ref shape_circle);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_shape_rect) && ConfigUtil.Str2Vec (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_shape_rect], ref shape_rect);
            all_ok = all_ok && kvPairs.ContainsKey(FieldName_CsvEffectFilterConfig.Field_Name_shape_sector) && ConfigUtil.Str2Vec (kvPairs[FieldName_CsvEffectFilterConfig.Field_Name_shape_sector], ref shape_sector);
            if (all_ok && null != func)
                all_ok &= func(this);
            return all_ok;
        }
    }

    public class CsvEffectFilterConfigSet
    {
        public string errMsg = string.Empty;

        public CsvEffectFilterConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvEffectFilterConfigSet items);
        public ConfigSetCheckFunc cfg_set_check_fun = null;
        public List<CsvEffectFilterConfig> cfg_vec = new List<CsvEffectFilterConfig> ();
        public Dictionary<int, CsvEffectFilterConfig> id_to_key = new Dictionary<int, CsvEffectFilterConfig>();

        public bool Load(string file_path)
        {
            using (CsvReader csv = new CsvReader(new StreamReader(file_path), true))
            {
                csv.MissingFieldAction = MissingFieldAction.ReplaceByEmpty;
                string[] headers = csv.GetFieldHeaders();
                List<int> fieldIdxList = new List<int>();
                try
                {
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_id));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_limit_num));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_limit_num_priority));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_unit_types));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_relations));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_anchor));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_shape_circle));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_shape_rect));
                    fieldIdxList.Add(csv.GetFieldIndex(FieldName_CsvEffectFilterConfig.Field_Name_shape_sector));
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
                    CsvEffectFilterConfig cfg = new CsvEffectFilterConfig();
                    if (!cfg.Init(kvPairs, cfg_check_fun))
                    {
                        errMsg = string.Format("CsvEffectFilterConfig Init Fail, row {0}", csv.CurrentRecordIndex);
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
                        errMsg = string.Format("CsvEffectFilterConfigSet repeated key id = {0}", cfg.id);
                        return false;
                    }
                    id_to_key[cfg.id] = cfg;
                }
            }

            if (null != cfg_set_check_fun)
            {
                if (!cfg_set_check_fun(this))
                {
                    errMsg = "CsvEffectFilterConfigSet cfg_set_check_fun fail";
                    return false;
                }
            }

            return true;
        }
    }
}