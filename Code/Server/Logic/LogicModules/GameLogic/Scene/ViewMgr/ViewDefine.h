#pragma once

#include <unordered_map>
#include <memory>
#include "stdint.h"
#include "Common/Geometry/Vector2.h"

namespace GameLogic
{
	class ViewObserver;
	class ViewVisualUnit;
	class ViewMgr;
	class SceneObject;
	using ViewObserverMap = std::unordered_map<uint64_t, ViewObserver *>;
	using ViewVisualUnitMap = std::unordered_map<uint64_t, ViewVisualUnit *>;

	extern const Vector2 InvalidViewPos;

	enum ViewCamp
	{
		ViewCamp_None = 0,
		ViewCamp_Red = 1 << 0,
		ViewCamp_Blue = 1 << 1,
		ViewCamp_All = -1
	};
}
