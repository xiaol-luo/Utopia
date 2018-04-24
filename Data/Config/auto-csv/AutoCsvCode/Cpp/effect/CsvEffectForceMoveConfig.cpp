#include "effect/CsvEffectForceMoveConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_id = "id";
     static const char * Field_Name_ignore_terrian = "ignore_terrian";
     static const char * Field_Name_result = "result";
     static const char * Field_Name_anchor = "anchor";
     static const char * Field_Name_angle = "angle";

    bool CsvEffectForceMoveConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_id], id);
        all_ok = all_ok && kvPairs.count(Field_Name_ignore_terrian) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_ignore_terrian], ignore_terrian);
        all_ok = all_ok && kvPairs.count(Field_Name_result) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_result], result);
        all_ok = all_ok && kvPairs.count(Field_Name_anchor) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_anchor], anchor);
        all_ok = all_ok && kvPairs.count(Field_Name_angle) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_angle], angle);
        if (all_ok && nullptr != func)
            all_ok &= func(this);
        return all_ok;
    }

    CsvEffectForceMoveConfigSet::~CsvEffectForceMoveConfigSet()
    {
        for (auto cfg : cfg_vec)
        {
            delete cfg;
        }
    }

    bool CsvEffectForceMoveConfigSet::Load(std::string file_path)
    {
        io::CSVReader<5, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_id,
            Field_Name_ignore_terrian,
            Field_Name_result,
            Field_Name_anchor,
            Field_Name_angle
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_id] = "";
        kvParis[Field_Name_ignore_terrian] = "";
        kvParis[Field_Name_result] = "";
        kvParis[Field_Name_anchor] = "";
        kvParis[Field_Name_angle] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_id],
            kvParis[Field_Name_ignore_terrian],
            kvParis[Field_Name_result],
            kvParis[Field_Name_anchor],
            kvParis[Field_Name_angle]
            ))
        {            
            if (++ curr_row <= 1)
                continue;
            if (kvParis[Field_Name_id].empty())
                continue;
            CsvEffectForceMoveConfig *cfg = new CsvEffectForceMoveConfig();
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
