#include "skill/CsvSkillConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_id = "id";
     static const char * Field_Name_name = "name";
     static const char * Field_Name_is_normal_attack = "is_normal_attack";
     static const char * Field_Name_use_way = "use_way";
     static const char * Field_Name_target_relations = "target_relations";
     static const char * Field_Name_target_types = "target_types";

    bool CsvSkillConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_id], id);
        all_ok = all_ok && kvPairs.count(Field_Name_name) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_name], name);
        all_ok = all_ok && kvPairs.count(Field_Name_is_normal_attack) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_is_normal_attack], is_normal_attack);
        all_ok = all_ok && kvPairs.count(Field_Name_use_way) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_use_way], use_way);
        all_ok = all_ok && kvPairs.count(Field_Name_target_relations) > 0 && ConfigUtil::Str2Vec (kvPairs[Field_Name_target_relations], target_relations);
        all_ok = all_ok && kvPairs.count(Field_Name_target_types) > 0 && ConfigUtil::Str2Vec (kvPairs[Field_Name_target_types], target_types);
        if (all_ok && nullptr != func)
            all_ok &= func(this);
        return all_ok;
    }

    CsvSkillConfigSet::~CsvSkillConfigSet()
    {
        for (auto cfg : cfg_vec)
        {
            delete cfg;
        }
    }

    bool CsvSkillConfigSet::Load(std::string file_path)
    {
        io::CSVReader<6, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_id,
            Field_Name_name,
            Field_Name_is_normal_attack,
            Field_Name_use_way,
            Field_Name_target_relations,
            Field_Name_target_types
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_id] = "";
        kvParis[Field_Name_name] = "";
        kvParis[Field_Name_is_normal_attack] = "";
        kvParis[Field_Name_use_way] = "";
        kvParis[Field_Name_target_relations] = "";
        kvParis[Field_Name_target_types] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_id],
            kvParis[Field_Name_name],
            kvParis[Field_Name_is_normal_attack],
            kvParis[Field_Name_use_way],
            kvParis[Field_Name_target_relations],
            kvParis[Field_Name_target_types]
            ))
        {            
            if (++ curr_row <= 1)
                continue;
            if (kvParis[Field_Name_id].empty())
                continue;
            CsvSkillConfig *cfg = new CsvSkillConfig();
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
