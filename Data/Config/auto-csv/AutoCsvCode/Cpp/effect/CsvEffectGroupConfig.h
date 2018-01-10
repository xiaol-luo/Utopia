#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectGroupConfig // 
    {
        int id = 0 ;
        std::vector<int> base_attrs;
        std::vector<std::vector<int>> extra_attrs;
        std::vector<std::vector<int>> percent_attrs;
        int need_guide = 0 ;
        int can_cancel_guide = 0 ;

        using ConfigCheckFunc = bool(*)(CsvEffectGroupConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectGroupConfigSet
    {
        ~CsvEffectGroupConfigSet();
        CsvEffectGroupConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(CsvEffectGroupConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectGroupConfig *> cfg_vec;
        std::map<int, CsvEffectGroupConfig *> id_to_key;
    };
}