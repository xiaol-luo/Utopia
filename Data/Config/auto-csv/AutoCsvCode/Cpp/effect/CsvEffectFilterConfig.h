#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvEffectFilterConfig // 
    {
        int id = 0 ;
        int limit_num = 0 ;
        std::string limit_num_priority;
        std::string unit_types;
        std::string relations;
        std::string anchor;
        int shape_circle = 0 ;
        std::vector<int> shape_rect;
        std::vector<int> shape_sector;

        using ConfigCheckFunc = std::function<bool(CsvEffectFilterConfig*)>;
        // using ConfigCheckFunc = bool(*)(CsvEffectFilterConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvEffectFilterConfigSet
    {
        ~CsvEffectFilterConfigSet();
        CsvEffectFilterConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        
        using ConfigSetCheckFunc = std::function<bool(CsvEffectFilterConfigSet*)>;
        //using ConfigSetCheckFunc = bool(*)(CsvEffectFilterConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvEffectFilterConfig *> cfg_vec;
        std::map<int, CsvEffectFilterConfig *> id_to_key;
    };
}