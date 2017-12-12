#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectAttrsConfig // 
    {
        int id = 0 ;
        std::map<int, int> attrs;
        bool reversible = 0 ;
        int last_time = 0 ;

        using ConfigCheckFunc = bool(*)(CsvEffectAttrsConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectAttrsConfigSet
    {
        ~CsvEffectAttrsConfigSet();
        CsvEffectAttrsConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(CsvEffectAttrsConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectAttrsConfig *> cfg_vec;
        std::map<int, CsvEffectAttrsConfig *> id_to_key;
    };
}