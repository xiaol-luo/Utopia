#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectAttrsConfig // 
    {
        int id = 0 ;
        std::vector<std::vector<int>> base_attrs;
        std::vector<std::vector<int>> extra_attrs;
        std::vector<std::vector<int>> percent_attrs;
        int hold_time_ms = 0 ;
        int unique_id = 0 ;

        using ConfigCheckFunc = std::function<bool(CsvEffectAttrsConfig*)>;
        // using ConfigCheckFunc = bool(*)(CsvEffectAttrsConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectAttrsConfigSet
    {
        ~CsvEffectAttrsConfigSet();
        CsvEffectAttrsConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        
        using ConfigSetCheckFunc = std::function<bool(CsvEffectAttrsConfigSet*)>;
        //using ConfigSetCheckFunc = bool(*)(CsvEffectAttrsConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectAttrsConfig *> cfg_vec;
        std::map<int, CsvEffectAttrsConfig *> id_to_key;
    };
}