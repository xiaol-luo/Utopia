#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct SkillLevelConfig // 
    {
        int id = 0 ;
        int level = 0 ;
        int preparing_span = 0 ;
        int releasing_span = 0 ;
        int using_span = 0 ;
        int lasting_span = 0 ;
        int comsume_mp = 0 ;
        int cd = 0 ;

        using ConfigCheckFunc = bool(*)(SkillLevelConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct SkillLevelConfigSet
    {
        ~SkillLevelConfigSet();
        SkillLevelConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(SkillLevelConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<SkillLevelConfig *> cfg_vec;
        std::map<int, std::vector<SkillLevelConfig *>> id_to_group;
    };
}