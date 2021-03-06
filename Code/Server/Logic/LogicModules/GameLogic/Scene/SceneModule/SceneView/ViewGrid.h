#pragma once

#include "GameLogic/Scene/Defines/ViewDefine.h"
#include <string.h>

namespace GameLogic
{
	class ViewMgr;
	class SceneUnit;

	struct ViewGrid
	{
		ViewGrid(int _id, int row, int col, Vector2 center, float size, EViewGridType grid_type);
		~ViewGrid();
		bool CanSee(EViewCamp camp);
		bool CanSee(int camp);

		int grid_id = -1;
		int row = -1;
		int col = -1;
		Vector2 center;
		float grid_size = 0;
		EViewGridType grid_type = EViewGrid_Ground;
		int grid_type_group = 0;
		
		std::array<int, EViewCamp_Observer + 1> observing_num = { 0 };
		std::unordered_map<uint64_t, std::weak_ptr<SceneUnit>> su_bodies;
	};
}
