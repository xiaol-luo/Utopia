#include "effect/CsvEffectAttrsConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_id = "id";
     static const char * Field_Name_base_attrs = "base_attrs";
     static const char * Field_Name_extra_attrs = "extra_attrs";
     static const char * Field_Name_percent_attrs = "percent_attrs";
     static const char * Field_Name_hold_time_ms = "hold_time_ms";
     static const char * Field_Name_unique_id = "unique_id";

    bool CsvEffectAttrsConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_id], id);
        all_ok = all_ok && kvPairs.count(Field_Name_base_attrs) > 0 && ConfigUtil::Str2VecVec (kvPairs[Field_Name_base_attrs], base_attrs);
        all_ok = all_ok && kvPairs.count(Field_Name_extra_attrs) > 0 && ConfigUtil::Str2VecVec (kvPairs[Field_Name_extra_attrs], extra_attrs);
        all_ok = all_ok && kvPairs.count(Field_Name_percent_attrs) > 0 && ConfigUtil::Str2VecVec (kvPairs[Field_Name_percent_attrs], percent_attrs);
        all_ok = all_ok && kvPairs.count(Field_Name_hold_time_ms) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_hold_time_ms], hold_time_ms);
        all_ok = all_ok && kvPairs.count(Field_Name_unique_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_unique_id], unique_id);
        if (all_ok && nullptr != func)
            all_ok &= func(this);
        return all_ok;
    }

    CsvEffectAttrsConfigSet::~CsvEffectAttrsConfigSet()
    {
        for (auto cfg : cfg_vec)
        {
            delete cfg;
        }
    }

    bool CsvEffectAttrsConfigSet::Load(std::string file_path)
    {
        io::CSVReader<6, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_id,
            Field_Name_base_attrs,
            Field_Name_extra_attrs,
            Field_Name_percent_attrs,
            Field_Name_hold_time_ms,
            Field_Name_unique_id
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_id] = "";
        kvParis[Field_Name_base_attrs] = "";
        kvParis[Field_Name_extra_attrs] = "";
        kvParis[Field_Name_percent_attrs] = "";
        kvParis[Field_Name_hold_time_ms] = "";
        kvParis[Field_Name_unique_id] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_id],
            kvParis[Field_Name_base_attrs],
            kvParis[Field_Name_extra_attrs],
            kvParis[Field_Name_percent_attrs],
            kvParis[Field_Name_hold_time_ms],
            kvParis[Field_Name_unique_id]
            ))
        {            
            if (++ curr_row <= 1)
                continue;
            if (kvParis[Field_Name_id].empty())
                continue;
            CsvEffectAttrsConfig *cfg = new CsvEffectAttrsConfig();
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
