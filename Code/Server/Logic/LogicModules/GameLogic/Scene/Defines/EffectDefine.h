#pragma once

#include <vector>
#include <unordered_map>

namespace GameLogic
{
	enum EEffectEndCase
	{
		EEffectEndCase_Both = 0,
		EEffectEndCase_Done,
		EEffectEndCase_Break,
	};

	using EffectIdVec = std::vector<int>;

	struct EndEffectId
	{
		EEffectEndCase end_case = EEffectEndCase_Both;
		int id = 0;
	};
	using EndEffectIdVec = std::vector<EndEffectId>;

	struct TimeLineEffectId
	{
		int id;
		int wait_ms;
	};
	using TimeLineEffectIdVec = std::vector<TimeLineEffectId>;

	enum EEffectStage
	{
		EEffectStage_Wait = 0,
		EEffectStage_Begin,
		EffectStage_Loop,
		EffectStage_End,
	};

	enum EEffectType
	{
		EEffectType_Hurt,
		EEffectType_Heal,
		EEffectType_Attr,
		EEffectType_ForceMove,
	};
}

