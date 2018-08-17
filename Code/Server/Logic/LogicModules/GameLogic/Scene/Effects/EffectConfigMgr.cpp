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
#include <sol.hpp>

namespace GameLogic
{
	EffectConfigMgr::EffectConfigMgr()
	{
	}

	EffectConfigMgr::~EffectConfigMgr()
	{
	}

	template <typename OutCfgType, typename CsvCfgVec>
	void BuildCfgHelp(CsvCfgVec &csvCfgVec, std::unordered_map<int, EffectConfigBase *> &effect_cfgs, sol::object lua_obj)
	{
		/*
		for (auto item : csvCfgVec)
		{
			auto cfg = new OutCfgType();
			assert(cfg->InitCfg(item, nullptr));
			auto ret = effect_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
			assert(ret.second);
		}
		*/

		if (lua_obj.is<sol::table>())
		{
			sol::table effect_json_cfs = lua_obj.as<sol::table>();
			for (auto kv_pair : effect_json_cfs)
			{
				sol::object key_obj = kv_pair.first;
				sol::object val_obj = kv_pair.second;

				if (val_obj.is<sol::table>())
				{
					sol::table tb = val_obj.as<sol::table>();
					auto cfg = new OutCfgType();
					assert(cfg->InitCfg(nullptr, (void **)&tb));
					auto ret = effect_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
					assert(ret.second);
				}
			}
		}
	}

	bool EffectConfigMgr::LoadCfg(Config::CsvConfigSets * csv_cfgs, void **param)
	{
		sol::table json_cfg = *(sol::table *)param;
		assert(json_cfg.valid());

		BuildCfgHelp<EffectGroupConfig>(csv_cfgs->csv_CsvEffectGroupConfigSet->cfg_vec, m_effect_cfgs, json_cfg["effect_group"]);
		BuildCfgHelp<EffectHurtConfig>(csv_cfgs->csv_CsvEffectHurtConfigSet->cfg_vec, m_effect_cfgs, json_cfg["effect_hurt"]);
		BuildCfgHelp<EffectAttrsConfig>(csv_cfgs->csv_CsvEffectAttrsConfigSet->cfg_vec, m_effect_cfgs, json_cfg["effect_attrs"]);
		BuildCfgHelp<EffectScriptConfig>(csv_cfgs->csv_CsvEffectScriptConfigSet->cfg_vec, m_effect_cfgs, sol::lua_nil);
		BuildCfgHelp<EffectSearcherConfig>(csv_cfgs->csv_CsvEffectSearcherConfigSet->cfg_vec, m_effect_cfgs, json_cfg["effect_searcher"]);
		BuildCfgHelp<EffectForceMoveConfig>(csv_cfgs->csv_CsvEffectForceMoveConfigSet->cfg_vec, m_effect_cfgs, json_cfg["effect_force_move"]);

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
