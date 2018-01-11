#include "EffectConfigMgr.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include "Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectHealConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"
#include "GameLogic/Scene/Effects/EffectHurt/EffectHurtConfig.h"
#include <assert.h>
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"
#include "GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectGroupConfig.h"
#include "GameLogic/Scene/Effects/EffectGroup/EffectGroupConfig.h"

namespace GameLogic
{
	EffectConfigMgr::EffectConfigMgr()
	{
	}

	EffectConfigMgr::~EffectConfigMgr()
	{
	}

	bool EffectConfigMgr::LoadCfg(Config::CsvConfigSets * csv_cfgs, void *param)
	{
		for (auto item : csv_cfgs->csv_CsvEffectHurtConfigSet->cfg_vec)
		{
			auto cfg = new EffectHurtConfig();
			assert(cfg->InitCfg(item));
			auto ret = m_effect_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
			assert(ret.second);
		}
		for (auto item : csv_cfgs->csv_CsvEffectAttrsConfigSet->cfg_vec)
		{
			auto cfg = new EffectAttrsConfig();
			assert(cfg->InitCfg(item));
			auto ret = m_effect_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
			assert(ret.second);
		}
		for (auto *item : csv_cfgs->csv_CsvEffectGroupConfigSet->cfg_vec)
		{
			auto cfg = new EffectGroupConfig();
			assert(cfg->InitCfg(item));
			auto ret = m_effect_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
			assert(ret.second);
		}
		return true;
	}

	const EffectConfigBase * EffectConfigMgr::GetCfg(int id)
	{
		auto it = m_effect_cfgs.find(id);
		if (m_effect_cfgs.end() != it)
			return it->second;
		return nullptr;
	}
}
