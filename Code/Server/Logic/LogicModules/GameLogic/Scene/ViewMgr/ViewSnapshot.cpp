#pragma once

#include "ViewSnapshot.h"
#include "ViewMgr.h"
#include "ViewGrid.h"

namespace GameLogic
{
	ViewSnapshot::ViewSnapshot()
	{

	}

	ViewSnapshot::~ViewSnapshot()
	{

	}

	void ViewSnapshot::Reset()
	{
		view_grids.clear();
		scene_objs.clear();
	}

	ViewSnapshotDifference ViewSnapshot::CalDifference(const ViewSnapshot * other)
	{
		 ViewSnapshotDifference diff;

		 if (view_grids.empty())
		 {
			 diff.miss_view_grids.assign(other->view_grids.begin(), other->view_grids.end());
		 }
		 else if (other->view_grids.empty())
		 {
			 diff.more_view_grids.assign(view_grids.begin(), view_grids.end());
		 }
		 else
		 {
			 size_t idx = 0; size_t other_idx = 0;
			 int gird_id = view_grids[0]->grid_id; int other_grid_id = other->view_grids[0]->grid_id;
		 }

		 return diff;
	}

	ViewSnapshotDifference::ViewSnapshotDifference()
	{
			
	}

	ViewSnapshotDifference::~ViewSnapshotDifference()
	{

	}

	void ViewSnapshotDifference::Reset()
	{
		more_scene_objs.clear();
		miss_scene_objs.clear();
		more_view_grids.clear();
		miss_view_grids.clear();
	}
}