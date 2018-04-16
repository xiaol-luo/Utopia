#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <array>
#include "stdint.h"
#include "Common/Geometry/Vector2.h"
#include "StdHashDefines.h"

namespace GameLogic
{
	class ViewMgr;
	struct ViewGrid;

	using ViewGridMap = std::unordered_map<int32_t, ViewGrid *>;
	using ViewGridSet = std::unordered_set<ViewGrid *>;
	using ViewGridVec = std::vector<ViewGrid *>;


	extern const Vector2 InvalidViewPos;
	const int VIEW_GRID_INVALID_IDX = -1;

	enum EViewCamp
	{
		EViewCamp_Red,
		EViewCamp_Blue,
		EViewCamp_Monster,
		EViewCamp_Observer,
		EViewCamp_All,
	};

	enum EViewGridType
	{
		EViewGrid_Ground,
		EViewGrid_Wall,
		EViewGrid_Grass
	};
}

namespace std
{
	/// sol_ignore
	template<>
	struct hash<GameLogic::EViewCamp>
	{
		typedef GameLogic::EViewCamp argument_type;
		typedef std::size_t result_type;

		result_type operator()(argument_type const &s) const
		{
			return (result_type)s;
		}
	};
}
