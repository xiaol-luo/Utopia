#include "CsvConfigSets.h"
#include "log/CsvLogConfig.h"
#include "Scene/CsvSceneConfig.h"
#include "skill/SkillConfig.h"
#include "skill/SkillLevelConfig.h"

namespace Config
{
    CsvConfigSets::~CsvConfigSets()
    {
        delete csv_CsvLogConfigSet;
        delete csv_CsvSceneConfigSet;
        delete csv_SkillConfigSet;
        delete csv_SkillLevelConfigSet;
    }

    bool CsvConfigSets::Load(std::string root_path)
    {
        while (!root_path.empty())
        {
            if (root_path.back() != '\\' && root_path.back() != '/' && root_path.back() != ' ')
                break;
            root_path.pop_back();
        }
        csv_CsvLogConfigSet = new CsvLogConfigSet;
        csv_CsvSceneConfigSet = new CsvSceneConfigSet;
        csv_SkillConfigSet = new SkillConfigSet;
        csv_SkillLevelConfigSet = new SkillLevelConfigSet;

        bool all_ok = true;
        if (all_ok)
        {
            all_ok = csv_CsvLogConfigSet->Load(root_path + '/' + "Log/CsvLogConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_CsvSceneConfigSet->Load(root_path + '/' + "scene/CsvSceneConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_SkillConfigSet->Load(root_path + '/' + "skill/SkillConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_SkillLevelConfigSet->Load(root_path + '/' + "skill/SkillLevelConfig.csv");
        }

        if (!all_ok)
        {
            delete csv_CsvLogConfigSet; csv_CsvLogConfigSet = nullptr;
            delete csv_CsvSceneConfigSet; csv_CsvSceneConfigSet = nullptr;
            delete csv_SkillConfigSet; csv_SkillConfigSet = nullptr;
            delete csv_SkillLevelConfigSet; csv_SkillLevelConfigSet = nullptr;
        }

        return all_ok;
    }
}