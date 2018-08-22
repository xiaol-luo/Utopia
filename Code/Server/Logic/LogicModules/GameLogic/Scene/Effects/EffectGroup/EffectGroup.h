#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"

namespace GameLogic
{
	class EffectGroupConfig;
	class EffectGroup: public EffectBase
	{
	public:
		EffectGroup(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectGroup();

	protected:
		virtual void OnLateBegin() override;
		virtual bool IsDone() override;

		const EffectGroupConfig *m_cfg = nullptr;
		bool m_is_began = false;
	};
}
