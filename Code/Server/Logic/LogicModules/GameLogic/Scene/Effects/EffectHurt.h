#pragma once

#include "EffectBase.h"

namespace GameLogic
{
	class EffectHurt : public EffectBase
	{
	public:
		EffectHurt(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectHurt();
	};
}
