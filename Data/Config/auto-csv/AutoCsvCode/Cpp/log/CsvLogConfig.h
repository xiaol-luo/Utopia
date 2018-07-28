#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Utils/ConfigUtil.h"

namespace Config
{
    struct CsvLogConfig // 
    {
        int id = 0 ;
        std::vector<int> alsoWritetoMe;
        int logger_type = 0 ;
        std::string name;
        int log_level = 0 ;
        std::string save_file;
        int rorating_max_size = 0 ;
        int rorating_max_files = 0 ;
        int daily_hour = 0 ;
        int daily_min = 0 ;

        using ConfigCheckFunc = std::function<bool(CsvLogConfig*)>;
        // using ConfigCheckFunc = bool(*)(CsvLogConfig *item);
        bool Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func);
    };

    struct CsvLogConfigSet
    {
        ~CsvLogConfigSet();
        CsvLogConfig::ConfigCheckFunc cfg_check_fun = nullptr;
        
        using ConfigSetCheckFunc = std::function<bool(CsvLogConfigSet*)>;
        //using ConfigSetCheckFunc = bool(*)(CsvLogConfigSet *items);
        ConfigSetCheckFunc cfg_set_check_fun = nullptr;
        bool Load(std::string file_path);
        
        std::vector<CsvLogConfig *> cfg_vec;
        std::map<int, CsvLogConfig *> id_to_key;
    };
}