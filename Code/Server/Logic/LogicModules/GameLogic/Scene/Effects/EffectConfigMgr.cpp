#include "EffectConfigMgr.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include "Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectHealConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectScriptConfig.h"
#include "GameLogic/Scene/Effects/EffectHurt/EffectHurtConfig.h"
#include <assert.h>
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"
#include "GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectGroupConfig.h"
#include "GameLogic/Scene/Effects/EffectGroup/EffectGroupConfig.h"
#include "GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"

#include "GameLogic/Scene/Effects/EffectSearcher/EffectSearcherConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectSearcherConfig.h"

#include "GameLogic/Scene/Effects/EffectForceMove/EffectForceMoveConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectForceMoveConfig.h"

namespace GameLogic
{
	EffectConfigMgr::EffectConfigMgr()
	{
	}

	EffectConfigMgr::~EffectConfigMgr()
	{
	}

	template <typename OutCfgType, typename CsvCfgVec>
	void BuildCfgHelp(CsvCfgVec &csvCfgVec, std::unordered_map<int, EffectConfigBase *> &effect_cfgs)
	{
		for (auto item : csvCfgVec)
		{
			auto cfg = new OutCfgType();
			assert(cfg->InitCfg(item));
			auto ret = effect_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
			assert(ret.second);
		}
	}

	bool EffectConfigMgr::LoadCfg(Config::CsvConfigSets * csv_cfgs, void *param)
	{
		BuildCfgHelp<EffectHurtConfig>(csv_cfgs->csv_CsvEffectHurtConfigSet->cfg_vec, m_effect_cfgs);
		BuildCfgHelp<EffectAttrsConfig>(csv_cfgs->csv_CsvEffectAttrsConfigSet->cfg_vec, m_effect_cfgs);
		BuildCfgHelp<EffectGroupConfig>(csv_cfgs->csv_CsvEffectGroupConfigSet->cfg_vec, m_effect_cfgs);
		BuildCfgHelp<EffectScriptConfig>(csv_cfgs->csv_CsvEffectScriptConfigSet->cfg_vec, m_effect_cfgs);
		BuildCfgHelp<EffectSearcherConfig>(csv_cfgs->csv_CsvEffectSearcherConfigSet->cfg_vec, m_effect_cfgs);
		BuildCfgHelp<EffectForceMoveConfig>(csv_cfgs->csv_CsvEffectForceMoveConfigSet->cfg_vec, m_effect_cfgs);
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
