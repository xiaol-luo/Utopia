#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectForceMoveConfig // 
    {
        int id = 0 ;
        bool ignore_terrian = 0 ;
        std::string result;
        std::string anchor;
        float angle = 0 ;

        using ConfigCheckFunc = std::function<bool(CsvEffectForceMoveConfig*)>;
        // using ConfigCheckFunc = bool(*)(CsvEffectForceMoveConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectForceMoveConfigSet
    {
        ~CsvEffectForceMoveConfigSet();
        CsvEffectForceMoveConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        
        using ConfigSetCheckFunc = std::function<bool(CsvEffectForceMoveConfigSet*)>;
        //using ConfigSetCheckFunc = bool(*)(CsvEffectForceMoveConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectForceMoveConfig *> cfg_vec;
        std::map<int, CsvEffectForceMoveConfig *> id_to_key;
    };
}