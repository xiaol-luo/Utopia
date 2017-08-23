#pragma once

#include <string>

namespace Config
{
    struct CsvLogConfigSet;

    struct CsvConfigSets
    {
        CsvLogConfigSet *csv_CsvLogConfigSet = nullptr;

        ~CsvConfigSets();
        bool Load(std::string root_path);
    };
}
