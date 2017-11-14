#pragma once

#include "ViewSnapshot.h"
#include "ViewMgr.h"
#include "ViewGrid.h"

namespace GameLogic
{
	ViewSnapshot::ViewSnapshot()
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
			 int gird_id = view_grids[idx]->grid_id; 
			 int other_grid_id = other->view_grids[other_idx]->grid_id;
			 while (idx < view_grids.size() && other_idx < other->view_grids.size())
			 {
				 if (gird_id == other_grid_id)
				 {
					 ++idx; ++other_idx;
					 gird_id = view_grids[idx]->grid_id; 
					 other_grid_id = other->view_grids[other_idx]->grid_id;
					 continue;
				 }
				 if (gird_id > other_grid_id)
				 {
					 diff.miss_view_grids.push_back(other->view_grids[other_idx]);
					 ++other_idx;
					 if (other_idx < other->view_grids.size())
						 other_grid_id = other->view_grids[other_idx]->grid_id;
				 }
				 if (gird_id < other_grid_id)
				 {
					 diff.more_view_grids.push_back(other->view_grids[idx]);
					 ++idx;
					 if (idx < view_grids.size())
						gird_id = view_grids[idx]->grid_id;
				 }
			 }
			 for (size_t i = idx; i < view_grids.size(); ++i)
			 {
				 diff.more_view_grids.push_back(view_grids[i]);
			 }
			 for (size_t i = other_idx; i < other->view_grids.size(); ++i)
			 {
				 diff.miss_view_grids.push_back(other->view_grids[i]);
			 }
		 }

		 for (auto so : scene_objs)
		 {
			 if (other->scene_objs.count(so.first) <= 0)
			 {
				 diff.more_scene_objs.insert(so);
			 }
		 }
		 for (auto so : other->scene_objs)
		 {
			 if (scene_objs.count(so.first) <= 0)
			 {
				 diff.miss_scene_objs.insert(so);
			 }
		 }

		 return diff;
	}

	ViewSnapshotDifference::ViewSnapshotDifference()
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