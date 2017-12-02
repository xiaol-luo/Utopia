#pragma once

#include <string>

namespace Config
{
    struct CsvLogConfigSet;
    struct CsvSceneConfigSet;
    struct SkillConfigSet;
    struct SkillLevelConfigSet;

    struct CsvConfigSets
    {
        CsvLogConfigSet *csv_CsvLogConfigSet = nullptr;
        CsvSceneConfigSet *csv_CsvSceneConfigSet = nullptr;
        SkillConfigSet *csv_SkillConfigSet = nullptr;
        SkillLevelConfigSet *csv_SkillLevelConfigSet = nullptr;

        ~CsvConfigSets();
        bool Load(std::string root_path);
    };
}
