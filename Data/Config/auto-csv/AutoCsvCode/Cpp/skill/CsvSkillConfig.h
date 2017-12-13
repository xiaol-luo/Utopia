#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvSkillConfig // 
    {
        int id = 0 ;
        std::string name;
        bool is_normal_attack = 0 ;
        int use_way = 0 ;
        std::vector<int> target_case;

        using ConfigCheckFunc = bool(*)(CsvSkillConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvSkillConfigSet
    {
        ~CsvSkillConfigSet();
        CsvSkillConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(CsvSkillConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvSkillConfig *> cfg_vec;
        std::map<int, CsvSkillConfig *> id_to_key;
    };
}