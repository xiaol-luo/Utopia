#include "CsvConfigSets.h"
#include "log/CsvLogConfig.h"
#include "Scene/CsvSceneConfig.h"
#include "skill/CsvSkillConfig.h"
#include "skill/CsvSkillLevelConfig.h"

namespace Config
{
    CsvConfigSets::~CsvConfigSets()
    {
        delete csv_CsvLogConfigSet;
        delete csv_CsvSceneConfigSet;
        delete csv_CsvSkillConfigSet;
        delete csv_CsvSkillLevelConfigSet;
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
        csv_CsvSkillConfigSet = new CsvSkillConfigSet;
        csv_CsvSkillLevelConfigSet = new CsvSkillLevelConfigSet;

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
            all_ok = csv_CsvSkillConfigSet->Load(root_path + '/' + "skill/CsvSkillConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_CsvSkillLevelConfigSet->Load(root_path + '/' + "skill/CsvSkillLevelConfig.csv");
        }

        if (!all_ok)
        {
            delete csv_CsvLogConfigSet; csv_CsvLogConfigSet = nullptr;
            delete csv_CsvSceneConfigSet; csv_CsvSceneConfigSet = nullptr;
            delete csv_CsvSkillConfigSet; csv_CsvSkillConfigSet = nullptr;
            delete csv_CsvSkillLevelConfigSet; csv_CsvSkillLevelConfigSet = nullptr;
        }

        return all_ok;
    }
}