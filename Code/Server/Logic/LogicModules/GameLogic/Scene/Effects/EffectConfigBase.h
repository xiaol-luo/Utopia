#pragma once

#include <vector>
#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace GameLogic
{
	class EffectBase;

	class EffectConfigBase
	{
	public:
		EffectConfigBase();
		virtual ~EffectConfigBase();

		virtual EffectBase * CreateEffect() = 0;
		const EffectIdVec & GetBeginEffectIds() { return m_begin_effect_ids; }
		const EndEffectIdVec & GetEndEffectIds() { return m_end_effect_ids; }
		const TimeLineEffectIdVec & GetHeartBeatEffectIds() { return m_heart_beat_effect_ids; }

	protected:
		int id;
		EffectIdVec m_begin_effect_ids;
		EndEffectIdVec m_end_effect_ids;
		TimeLineEffectIdVec m_heart_beat_effect_ids;
	};
}