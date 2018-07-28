#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectScriptConfig // 
    {
        int id = 0 ;
        std::string class_name;
        std::string script_param;

        using ConfigCheckFunc = std::function<bool(CsvEffectScriptConfig*)>;
        // using ConfigCheckFunc = bool(*)(CsvEffectScriptConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectScriptConfigSet
    {
        ~CsvEffectScriptConfigSet();
        CsvEffectScriptConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        
        using ConfigSetCheckFunc = std::function<bool(CsvEffectScriptConfigSet*)>;
        //using ConfigSetCheckFunc = bool(*)(CsvEffectScriptConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectScriptConfig *> cfg_vec;
        std::map<int, CsvEffectScriptConfig *> id_to_key;
    };
}