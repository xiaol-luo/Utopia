#include "EffectHurtConfig.h"
#include "EffectHurt.h"

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectHurtConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectHurt>(this, scene_effects, effect_key);
	}
}

