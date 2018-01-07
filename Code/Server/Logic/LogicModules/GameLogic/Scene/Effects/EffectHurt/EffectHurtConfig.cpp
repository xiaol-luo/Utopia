#include "EffectHurtConfig.h"
#include "EffectHurt.h"
#include "Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"
#include <assert.h>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectHurtConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectHurt>(this, scene_effects, effect_key);
	}

	bool EffectHurtConfig::InitCfg(const Config::CsvEffectHurtConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		m_reversible = false;
		assert(csv_cfg->value > 0);
		m_hurt = csv_cfg->value;
		return true;
	}
}

