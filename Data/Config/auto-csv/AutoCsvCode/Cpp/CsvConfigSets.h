#pragma once

#include <string>

namespace Config
{
    struct CsvLogConfigSet;
    struct CsvSceneConfigSet;
    struct CsvSkillConfigSet;
    struct CsvSkillLevelConfigSet;
    struct CsvEffectHurtConfigSet;
    struct CsvEffectHealConfigSet;
    struct CsvEffectAttrsConfigSet;

    struct CsvConfigSets
    {
        CsvLogConfigSet *csv_CsvLogConfigSet = nullptr;
        CsvSceneConfigSet *csv_CsvSceneConfigSet = nullptr;
        CsvSkillConfigSet *csv_CsvSkillConfigSet = nullptr;
        CsvSkillLevelConfigSet *csv_CsvSkillLevelConfigSet = nullptr;
        CsvEffectHurtConfigSet *csv_CsvEffectHurtConfigSet = nullptr;
        CsvEffectHealConfigSet *csv_CsvEffectHealConfigSet = nullptr;
        CsvEffectAttrsConfigSet *csv_CsvEffectAttrsConfigSet = nullptr;

        ~CsvConfigSets();
        bool Load(std::string root_path);
    };
}
