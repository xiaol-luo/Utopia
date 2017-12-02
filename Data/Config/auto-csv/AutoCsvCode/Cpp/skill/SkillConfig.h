#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct SkillConfig // 
    {
        int id = 0 ;
        std::string name;

        using ConfigCheckFunc = bool(*)(SkillConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct SkillConfigSet
    {
        ~SkillConfigSet();
        SkillConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(SkillConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<SkillConfig *> cfg_vec;
        std::map<int, SkillConfig *> id_to_key;
    };
}