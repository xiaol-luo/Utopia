#include "EffectBase.h"

namespace GameLogic
{
	EffectBase::EffectBase(EffectConfigBase *cfg, uint64_t effect_key)
	{
	}
	EffectBase::~EffectBase()
	{
	}
	void EffectBase::Begin(std::shared_ptr<Skill> skill, std::shared_ptr<EffectBase> trigger_effect)
	{
	}
	void EffectBase::End()
	{
	}
	void EffectBase::HeartBeat()
	{
	}
}
