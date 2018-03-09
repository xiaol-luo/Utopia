#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Effects/EffectBase.h"
#include <unordered_map>

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

	protected:
		virtual void OnUpdate() override;

	protected:
		uint64_t m_last_effect_key = 0;
		std::unordered_map<uint64_t, std::shared_ptr<EffectBase>> m_effects;
		std::unordered_set<uint64_t> m_removed_effects;
		void CheckRemoveEffects();
	};
}
