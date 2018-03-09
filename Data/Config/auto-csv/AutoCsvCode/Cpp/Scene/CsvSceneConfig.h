#pragma once
#include <string>
#include <vector>
#include <map>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvSceneConfig // 
    {
        int id = 0 ;
        std::string terrain_file_path;

        using ConfigCheckFunc = bool(*)(CsvSceneConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvSceneConfigSet
    {
        ~CsvSceneConfigSet();
        CsvSceneConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        using ConfigSetCheckFunc = bool(*)(CsvSceneConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvSceneConfig *> cfg_vec;
        std::map<int, CsvSceneConfig *> id_to_key;
    };
}