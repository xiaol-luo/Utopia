#include "EffectHurtConfig.h"
#include "EffectHurt.h"
#include "Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"
#include <assert.h>
#include <sol.hpp>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectHurtConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectHurt>(this, scene_effects, effect_key);
	}

	bool EffectHurtConfig::InitCfg(const Config::CsvEffectHurtConfig * csv_cfg, void **param)
	{
		sol::table json_cfg = *(sol::table *)param;
		if (json_cfg.valid())
		{
			m_id = json_cfg["id"];
			m_name = json_cfg["name"];
			m_hurt = json_cfg["val"];
		}
		else if (nullptr != csv_cfg)
		{
			m_id = csv_cfg->id;
			m_reversible = false;
			m_hurt = csv_cfg->value;
		}

		return true;
	}
}

