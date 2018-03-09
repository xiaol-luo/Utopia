#include "effect/CsvEffectFilterConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_id = "id";
     static const char * Field_Name_limit_num = "limit_num";
     static const char * Field_Name_limit_num_priority = "limit_num_priority";
     static const char * Field_Name_unit_types = "unit_types";
     static const char * Field_Name_relations = "relations";
     static const char * Field_Name_anchor = "anchor";
     static const char * Field_Name_shape_circle = "shape_circle";
     static const char * Field_Name_shape_rect = "shape_rect";
     static const char * Field_Name_shape_sector = "shape_sector";

    bool CsvEffectFilterConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_id], id);
        all_ok = all_ok && kvPairs.count(Field_Name_limit_num) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_limit_num], limit_num);
        all_ok = all_ok && kvPairs.count(Field_Name_limit_num_priority) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_limit_num_priority], limit_num_priority);
        all_ok = all_ok && kvPairs.count(Field_Name_unit_types) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_unit_types], unit_types);
        all_ok = all_ok && kvPairs.count(Field_Name_relations) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_relations], relations);
        all_ok = all_ok && kvPairs.count(Field_Name_anchor) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_anchor], anchor);
        all_ok = all_ok && kvPairs.count(Field_Name_shape_circle) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_shape_circle], shape_circle);
        all_ok = all_ok && kvPairs.count(Field_Name_shape_rect) > 0 && ConfigUtil::Str2Vec (kvPairs[Field_Name_shape_rect], shape_rect);
        all_ok = all_ok && kvPairs.count(Field_Name_shape_sector) > 0 && ConfigUtil::Str2Vec (kvPairs[Field_Name_shape_sector], shape_sector);
        if (all_ok && nullptr != func)
            all_ok &= func(this);
        return all_ok;
    }

    CsvEffectFilterConfigSet::~CsvEffectFilterConfigSet()
    {
        for (auto cfg : cfg_vec)
        {
            delete cfg;
        }
    }

    bool CsvEffectFilterConfigSet::Load(std::string file_path)
    {
        io::CSVReader<9, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_id,
            Field_Name_limit_num,
            Field_Name_limit_num_priority,
            Field_Name_unit_types,
            Field_Name_relations,
            Field_Name_anchor,
            Field_Name_shape_circle,
            Field_Name_shape_rect,
            Field_Name_shape_sector
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_id] = "";
        kvParis[Field_Name_limit_num] = "";
        kvParis[Field_Name_limit_num_priority] = "";
        kvParis[Field_Name_unit_types] = "";
        kvParis[Field_Name_relations] = "";
        kvParis[Field_Name_anchor] = "";
        kvParis[Field_Name_shape_circle] = "";
        kvParis[Field_Name_shape_rect] = "";
        kvParis[Field_Name_shape_sector] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_id],
            kvParis[Field_Name_limit_num],
            kvParis[Field_Name_limit_num_priority],
            kvParis[Field_Name_unit_types],
            kvParis[Field_Name_relations],
            kvParis[Field_Name_anchor],
            kvParis[Field_Name_shape_circle],
            kvParis[Field_Name_shape_rect],
            kvParis[Field_Name_shape_sector]
            ))
        {            
            if (++ curr_row <= 1)
                continue;
            if (kvParis[Field_Name_id].empty())
                continue;
            CsvEffectFilterConfig *cfg = new CsvEffectFilterConfig();
            all_ok &= cfg->Init(kvParis, cfg_check_fun);
            if (!all_ok)
                break;
            cfg_vec.push_back(cfg);
        }
        if (all_ok)
        {
            // gen key
            for (auto cfg : cfg_vec)
            {
                {
                    if (id_to_key.count(cfg->id) > 0)
                    {
                        all_ok = false;
                        break;
                    }
                    id_to_key[cfg->id] = cfg;
                }
            }
        }
        if (nullptr != cfg_set_check_fun)
        {
            all_ok = all_ok && cfg_set_check_fun(this);
        }
        return all_ok;
    }
}
