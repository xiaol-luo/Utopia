#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include "stdint.h"
#include "Common/Geometry/Vector2.h"

namespace GameLogic
{
	class ViewMgr;
	class SceneObject;
	struct ViewGrid;
	class ViewUnit;

	using ViewGridMap = std::unordered_map<int32_t, ViewGrid *>;
	using ViewGridSet = std::unordered_set<ViewGrid *>;
	using ViewGridVec = std::vector<ViewGrid *>;

	using ViewUnitMap = std::unordered_map<int64_t, ViewUnit *>;
	using ViewUnitSet = std::unordered_set<ViewUnit *>;


	extern const Vector2 InvalidViewPos;
	const int VIEW_GRID_INVALID_IDX = -1;

	enum EViewCamp
	{
		EViewCamp_Red,
		EViewCamp_Blue,
		EViewCamp_Observer,
	};

	enum EViewGridType
	{
		EViewGrid_Ground,
		EViewGrid_Wall,
		EViewGrid_Grass
	};
}
