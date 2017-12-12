#pragma once

#include <vector>
#include <unordered_map>
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/Vector3.h"

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
		int id = 0;
		int wait_ms = 0;
	};
	using TimeLineEffectIdVec = std::vector<TimeLineEffectId>;
	struct TimeLineEffectIdsConfig
	{
		TimeLineEffectIdVec effect_ids;
		int min_wait_ms = -1;
		int max_wait_ms = -1;
	};

	enum EEffectStage
	{
		EEffectStage_Wait = 0,
		EEffectStage_Begin,
		EEffectStage_Loop,
		EEffectStage_End,
	};

	enum EEffectType
	{
		EEffectType_Hurt,
		EEffectType_Heal,
		EEffectType_Attr,
		EEffectType_ForceMove,
	};
}

