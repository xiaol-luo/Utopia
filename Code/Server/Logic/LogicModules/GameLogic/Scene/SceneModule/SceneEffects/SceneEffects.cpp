#include "SceneEffects.h"

namespace GameLogic
{
	SceneEffects::SceneEffects() : SceneModule(MODULE_TYPE)
	{

	}

	SceneEffects::~SceneEffects()
	{

	}
	std::shared_ptr<EffectBase> SceneEffects::CreateEffect(int effect_id)
	{
		return std::shared_ptr<EffectBase>();
	}
}


