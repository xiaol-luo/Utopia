#include "skill/CsvSkillLevelConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_id = "id";
     static const char * Field_Name_level = "level";
     static const char * Field_Name_preparing_span = "preparing_span";
     static const char * Field_Name_releasing_span = "releasing_span";
     static const char * Field_Name_lasting_span = "lasting_span";
     static const char * Field_Name_comsume_mp = "comsume_mp";
     static const char * Field_Name_cd = "cd";
     static const char * Field_Name_cast_distance = "cast_distance";
     static const char * Field_Name_can_move = "can_move";

    bool CsvSkillLevelConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_id], id);
        all_ok = all_ok && kvPairs.count(Field_Name_level) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_level], level);
        all_ok = all_ok && kvPairs.count(Field_Name_preparing_span) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_preparing_span], preparing_span);
        all_ok = all_ok && kvPairs.count(Field_Name_releasing_span) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_releasing_span], releasing_span);
        all_ok = all_ok && kvPairs.count(Field_Name_lasting_span) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_lasting_span], lasting_span);
        all_ok = all_ok && kvPairs.count(Field_Name_comsume_mp) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_comsume_mp], comsume_mp);
        all_ok = all_ok && kvPairs.count(Field_Name_cd) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_cd], cd);
        all_ok = all_ok && kvPairs.count(Field_Name_cast_distance) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_cast_distance], cast_distance);
        all_ok = all_ok && kvPairs.count(Field_Name_can_move) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_can_move], can_move);
        if (all_ok && nullptr != func)
            all_ok &= func(this);
        return all_ok;
    }

    CsvSkillLevelConfigSet::~CsvSkillLevelConfigSet()
    {
        for (auto cfg : cfg_vec)
        {
            delete cfg;
        }
    }

    bool CsvSkillLevelConfigSet::Load(std::string file_path)
    {
        io::CSVReader<9, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_id,
            Field_Name_level,
            Field_Name_preparing_span,
            Field_Name_releasing_span,
            Field_Name_lasting_span,
            Field_Name_comsume_mp,
            Field_Name_cd,
            Field_Name_cast_distance,
            Field_Name_can_move
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_id] = "";
        kvParis[Field_Name_level] = "";
        kvParis[Field_Name_preparing_span] = "";
        kvParis[Field_Name_releasing_span] = "";
        kvParis[Field_Name_lasting_span] = "";
        kvParis[Field_Name_comsume_mp] = "";
        kvParis[Field_Name_cd] = "";
        kvParis[Field_Name_cast_distance] = "";
        kvParis[Field_Name_can_move] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_id],
            kvParis[Field_Name_level],
            kvParis[Field_Name_preparing_span],
            kvParis[Field_Name_releasing_span],
            kvParis[Field_Name_lasting_span],
            kvParis[Field_Name_comsume_mp],
            kvParis[Field_Name_cd],
            kvParis[Field_Name_cast_distance],
            kvParis[Field_Name_can_move]
            ))
        {            
            if (++ curr_row <= 1)
                continue;
            if (kvParis[Field_Name_id].empty())
                continue;
            CsvSkillLevelConfig *cfg = new CsvSkillLevelConfig();
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
                    auto it = id_to_group.find(cfg->id);
                    if (id_to_group.end() == it)
                    {
                        auto ret_it = id_to_group.insert(std::make_pair(cfg->id, std::vector<CsvSkillLevelConfig *>()));
                        if (!ret_it.second)
                        {
                            all_ok = false;
                            break;
                        }
                        it = ret_it.first;
                    }
                    it->second.push_back(cfg);
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
