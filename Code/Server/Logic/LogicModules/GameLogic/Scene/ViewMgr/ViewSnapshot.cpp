#pragma once

#include "ViewSnapshot.h"
#include "ViewMgr.h"
#include "ViewGrid.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"

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

	ViewSnapshotDifference ViewSnapshot::CalDifference(const ViewSnapshot * other) const
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
					 if (idx < view_grids.size() && other_idx < other->view_grids.size())
					 {
						 assert(gird_id < view_grids[idx]->grid_id);
						 assert(other_grid_id < other->view_grids[other_idx]->grid_id);

						 gird_id = view_grids[idx]->grid_id;
						 other_grid_id = other->view_grids[other_idx]->grid_id;
					 }
				 }
				 else if (gird_id > other_grid_id)
				 {
					 diff.miss_view_grids.push_back(other->view_grids[other_idx]);
					 ++other_idx;
					 if (other_idx < other->view_grids.size())
					 {
						 assert(other_grid_id < other->view_grids[other_idx]->grid_id);
						 other_grid_id = other->view_grids[other_idx]->grid_id;
					 }
						 
				 }
				 else if (gird_id < other_grid_id)
				 {
					 diff.more_view_grids.push_back(view_grids[idx]);
					 ++idx;
					 if (idx < view_grids.size())
					 {
						 assert(gird_id < view_grids[idx]->grid_id);
						 gird_id = view_grids[idx]->grid_id;
					 }
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

	//////////////////////////////////////////////////////////////////////////


	void ViewSnapshotDifference::PrintLog()
	{/*

		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> miss_scene_objs;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> more_scene_objs;
		ViewGridVec miss_view_grids;
		ViewGridVec more_view_grids;
		*/

		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
			"-----------------------------------------------------------------------------");
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference miss_scene_objs {0}", miss_scene_objs.size());
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference more_scene_objs {0}", more_scene_objs.size());
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference miss_view_grids {0}", miss_view_grids.size());
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference more_view_grids {0}", more_view_grids.size());
	}
}