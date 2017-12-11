#pragma once

#include "EffectConfigBase.h"
#include "EffectConfigMgr.h"
#include <memory>

namespace GameLogic
{
	class Skill;

	class EffectBase : public std::enable_shared_from_this<EffectBase>
	{
	public:
		EffectBase(EffectConfigBase *cfg, uint64_t effect_key);
		virtual ~EffectBase();

		virtual void Begin(std::shared_ptr<Skill> skill, std::shared_ptr<EffectBase> trigger_effect);
		virtual void End();
		virtual void HeartBeat();

		uint64_t GetKey() { return m_effect_key; }
		const EffectConfigBase * GetCfg() { return m_cfg; }
		std::shared_ptr<Skill> GetSkill() { return m_skill; }

	protected:
		uint64_t m_effect_key = 0;
		const EffectConfigBase *m_cfg = nullptr;
		std::shared_ptr<Skill> m_skill = nullptr;
	};
}
