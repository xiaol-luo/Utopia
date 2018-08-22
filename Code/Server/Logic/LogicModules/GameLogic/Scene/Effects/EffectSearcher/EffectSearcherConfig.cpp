#include "EffectSearcherConfig.h"
#include "EffectSearcher.h"
#include "Config/AutoCsvCode/effect/CsvEffectSearcherConfig.h"
#include <assert.h>
#include <sol.hpp>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectSearcherConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectSearcher>(this, scene_effects, effect_key);
	}

	bool EffectSearcherConfig::InitCfg(const Config::CsvEffectSearcherConfig * csv_cfg, void **param)
	{
		sol::table json_cfg = *(sol::table *)param;
		if (json_cfg.valid())
		{
			m_id = json_cfg["id"];
			m_name = json_cfg["name"];
			m_filter_id = json_cfg["filter_id"];
			m_is_extract = json_cfg["is_extract"];
			sol::table tb = json_cfg["base_attrs"];
			for (auto kv_pair : tb)
			{
				int effect_id = kv_pair.second.as<int>();
				m_effect_ids.push_back(effect_id);
			}
		}
		else if (nullptr != csv_cfg)
		{
			m_id = csv_cfg->id;
			m_reversible = false;
			m_filter_id = csv_cfg->filter_id;
			m_effect_ids = csv_cfg->effect_ids;
		}

		return true;
	}
}

