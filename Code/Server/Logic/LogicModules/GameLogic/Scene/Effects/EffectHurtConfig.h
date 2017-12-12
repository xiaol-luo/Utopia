#pragma once

#include "EffectConfigBase.h"

namespace GameLogic
{
	class EffectHurtConfig : public EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect() const;

	public:
		void SetHurt(int val) { m_hurt = val; }
		int GetHurt() { return m_hurt; }
	protected:
		int m_hurt = 0;
	};
}
