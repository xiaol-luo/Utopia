#include "EffectConfigMgr.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include "Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectHealConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"
#include "GameLogic/Scene/Effects/EffectHurtConfig.h"
#include <assert.h>

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
		for (Config::CsvEffectHurtConfig *item : csv_cfgs->csv_CsvEffectHurtConfigSet->cfg_vec)
		{
			EffectHurtConfig *cfg = new EffectHurtConfig();
			cfg->SetId(item->id);
			cfg->SetReversible(false);
			assert(item->value > 0);
			cfg->SetHurt(item->value);
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
