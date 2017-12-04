#pragma once

#include <string>

namespace Config
{
    struct CsvLogConfigSet;
    struct CsvSceneConfigSet;
    struct CsvSkillConfigSet;
    struct CsvSkillLevelConfigSet;

    struct CsvConfigSets
    {
        CsvLogConfigSet *csv_CsvLogConfigSet = nullptr;
        CsvSceneConfigSet *csv_CsvSceneConfigSet = nullptr;
        CsvSkillConfigSet *csv_CsvSkillConfigSet = nullptr;
        CsvSkillLevelConfigSet *csv_CsvSkillLevelConfigSet = nullptr;

        ~CsvConfigSets();
        bool Load(std::string root_path);
    };
}
