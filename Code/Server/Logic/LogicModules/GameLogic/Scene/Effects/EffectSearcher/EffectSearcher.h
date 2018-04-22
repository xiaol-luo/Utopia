#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"

namespace GameLogic
{
	class EffectSearcherConfig;
	class EffectSearcher : public EffectBase
	{
	public:
		EffectSearcher(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectSearcher();

	protected:
		virtual void OnBegin() override;
		virtual bool IsDone() { return m_is_done; }
	protected:
		const EffectSearcherConfig *m_cfg = nullptr;
		bool m_is_done = false;
	};
}
