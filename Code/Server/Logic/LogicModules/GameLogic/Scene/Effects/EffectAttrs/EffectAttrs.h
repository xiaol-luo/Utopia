#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"

namespace GameLogic
{
	class EffectAttrsConfig;

	class EffectAttrs : public EffectBase
	{
	public:
		EffectAttrs(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectAttrs();

	protected:
		virtual void OnBegin() override;
		virtual void OnLateEnd(EEffectEndCase end_case) override;
		virtual void OnLoop(int64_t now_ms, int64_t delta_ms) override;
		virtual bool IsDone() override  { return m_is_done; } 
	protected:
		const EffectAttrsConfig *m_cfg = nullptr;
		bool m_is_done = false;
	};
}
