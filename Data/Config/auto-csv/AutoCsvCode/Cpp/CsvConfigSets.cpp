#include "CsvConfigSets.h"
#include "log/CsvLogConfig.h"
#include "Scene/CsvSceneConfig.h"
#include "skill/CsvSkillConfig.h"
#include "skill/CsvSkillLevelConfig.h"
#include "effect/CsvEffectHurtConfig.h"
#include "effect/CsvEffectHealConfig.h"
#include "effect/CsvEffectAttrsConfig.h"
#include "effect/CsvEffectFilterConfig.h"
#include "effect/CsvEffectGroupConfig.h"

namespace Config
{
    CsvConfigSets::~CsvConfigSets()
    {
        delete csv_CsvLogConfigSet;
        delete csv_CsvSceneConfigSet;
        delete csv_CsvSkillConfigSet;
        delete csv_CsvSkillLevelConfigSet;
        delete csv_CsvEffectHurtConfigSet;
        delete csv_CsvEffectHealConfigSet;
        delete csv_CsvEffectAttrsConfigSet;
        delete csv_CsvEffectFilterConfigSet;
        delete csv_CsvEffectGroupConfigSet;
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
        csv_CsvEffectHurtConfigSet = new CsvEffectHurtConfigSet;
        csv_CsvEffectHealConfigSet = new CsvEffectHealConfigSet;
        csv_CsvEffectAttrsConfigSet = new CsvEffectAttrsConfigSet;
        csv_CsvEffectFilterConfigSet = new CsvEffectFilterConfigSet;
        csv_CsvEffectGroupConfigSet = new CsvEffectGroupConfigSet;

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
        if (all_ok)
        {
            all_ok = csv_CsvEffectHurtConfigSet->Load(root_path + '/' + "effect/CsvEffectHurtConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_CsvEffectHealConfigSet->Load(root_path + '/' + "effect/CsvEffectHealConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_CsvEffectAttrsConfigSet->Load(root_path + '/' + "effect/CsvEffectAttrsConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_CsvEffectFilterConfigSet->Load(root_path + '/' + "effect/CsvEffectFilterConfig.csv");
        }
        if (all_ok)
        {
            all_ok = csv_CsvEffectGroupConfigSet->Load(root_path + '/' + "effect/CsvEffectGroupConfig.csv");
        }

        if (!all_ok)
        {
            delete csv_CsvLogConfigSet; csv_CsvLogConfigSet = nullptr;
            delete csv_CsvSceneConfigSet; csv_CsvSceneConfigSet = nullptr;
            delete csv_CsvSkillConfigSet; csv_CsvSkillConfigSet = nullptr;
            delete csv_CsvSkillLevelConfigSet; csv_CsvSkillLevelConfigSet = nullptr;
            delete csv_CsvEffectHurtConfigSet; csv_CsvEffectHurtConfigSet = nullptr;
            delete csv_CsvEffectHealConfigSet; csv_CsvEffectHealConfigSet = nullptr;
            delete csv_CsvEffectAttrsConfigSet; csv_CsvEffectAttrsConfigSet = nullptr;
            delete csv_CsvEffectFilterConfigSet; csv_CsvEffectFilterConfigSet = nullptr;
            delete csv_CsvEffectGroupConfigSet; csv_CsvEffectGroupConfigSet = nullptr;
        }

        return all_ok;
    }
}