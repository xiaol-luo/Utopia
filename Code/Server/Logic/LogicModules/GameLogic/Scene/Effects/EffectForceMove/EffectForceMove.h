#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"

namespace GameLogic
{
	class EffectForceMoveConfig;
	class EffectForceMove : public EffectBase
	{
	public:
		EffectForceMove(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectForceMove();

	protected:
		virtual void OnBegin() override;
		virtual bool IsDone() { return m_is_done; }
	protected:
		const EffectForceMoveConfig *m_cfg = nullptr;
		bool m_is_done = false;
	};
}
