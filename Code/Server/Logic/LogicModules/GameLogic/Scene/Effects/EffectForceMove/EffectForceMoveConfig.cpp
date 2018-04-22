#include "EffectForceMoveConfig.h"
#include "EffectForceMove.h"
#include "Config/AutoCsvCode/effect/CsvEffectForceMoveConfig.h"
#include <assert.h>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectForceMoveConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectForceMove>(this, scene_effects, effect_key);
	}

	bool EffectForceMoveConfig::InitCfg(const Config::CsvEffectForceMoveConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		m_reversible = false;
		return true;
	}
}

