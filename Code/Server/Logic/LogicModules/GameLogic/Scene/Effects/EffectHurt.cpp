#include "EffectHurt.h"

namespace GameLogic
{
	EffectHurt::EffectHurt(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key) : EffectBase(cfg, scene_effects, effect_key)
	{
	}

	EffectHurt::~EffectHurt()
	{
	}
}