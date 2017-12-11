#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Effects/EffectBase.h"

namespace GameLogic
{
	class SceneEffects : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE = ESceneModule_Effects;
	public:
		SceneEffects();
		virtual ~SceneEffects() override;

		std::shared_ptr<EffectBase> CreateEffect(int effect_id);
		bool AddEffect(std::shared_ptr<EffectBase> effect);
		void RemoveEffect(uint64_t effect_key);
	};
}
