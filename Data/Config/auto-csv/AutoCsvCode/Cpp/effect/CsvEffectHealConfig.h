#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectHealConfig // 
    {
        int id = 0 ;
        int value = 0 ;

        using ConfigCheckFunc = bool(*)(CsvEffectHealConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectHealConfigSet
    {
        ~CsvEffectHealConfigSet();
        CsvEffectHealConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(CsvEffectHealConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectHealConfig *> cfg_vec;
        std::map<int, CsvEffectHealConfig *> id_to_key;
    };
}