#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectSearcherConfig // 
    {
        int id = 0 ;
        int filter_id = 0 ;
        std::vector<int> effect_ids;

        using ConfigCheckFunc = bool(*)(CsvEffectSearcherConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectSearcherConfigSet
    {
        ~CsvEffectSearcherConfigSet();
        CsvEffectSearcherConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(CsvEffectSearcherConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectSearcherConfig *> cfg_vec;
        std::map<int, CsvEffectSearcherConfig *> id_to_key;
    };
}