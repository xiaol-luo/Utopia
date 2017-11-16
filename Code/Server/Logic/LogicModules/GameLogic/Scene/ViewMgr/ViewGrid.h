#pragma once

#include "ViewDefine.h"

namespace GameLogic
{
	class ViewMgr;

	struct ViewGrid
	{
		ViewGrid(ViewMgr *mgr, int _id, int row, int col, Vector2 center, float size, EViewGridType grid_type);
		~ViewGrid();
		bool CanSee(EViewCamp camp);
		bool CanSee(int camp);

		int grid_id = -1;
		int row = -1;
		int col = -1;
		ViewMgr *view_mgr = nullptr;
		Vector2 center;
		float grid_size = 0;
		EViewGridType grid_type = EViewGrid_Ground;
		int grid_type_group = 0;
		int observing_num[EViewCamp_All];
		ViewUnitMap body_units;
	};
}
