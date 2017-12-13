#pragma once

#include "EffectBase.h"

namespace GameLogic
{
	class EffectHurtConfig;
	class EffectHurt : public EffectBase
	{
	public:
		EffectHurt(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectHurt();

	protected:
		virtual void OnBegin(std::shared_ptr<Skill> skill, uint64_t target_suid, Vector3 pos, Vector2 dir);
		virtual bool IsDone() { return m_is_done; }
	protected:
		const EffectHurtConfig *m_cfg = nullptr;
		bool m_is_done = false;
	};
}
