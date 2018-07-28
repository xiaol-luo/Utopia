#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvSkillLevelConfig // 
    {
        int id = 0 ;
        int level = 0 ;
        int preparing_span = 0 ;
        int releasing_span = 0 ;
        int lasting_span = 0 ;
        int comsume_mp = 0 ;
        int cd = 0 ;
        float cast_distance = 0 ;
        bool can_move = 0 ;
        std::vector<int> effect_ids;

        using ConfigCheckFunc = std::function<bool(CsvSkillLevelConfig*)>;
        // using ConfigCheckFunc = bool(*)(CsvSkillLevelConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvSkillLevelConfigSet
    {
        ~CsvSkillLevelConfigSet();
        CsvSkillLevelConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        
        using ConfigSetCheckFunc = std::function<bool(CsvSkillLevelConfigSet*)>;
        //using ConfigSetCheckFunc = bool(*)(CsvSkillLevelConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvSkillLevelConfig *> cfg_vec;
        std::map<int, std::vector<CsvSkillLevelConfig *>> id_to_group;
    };
}