#include "ViewSnapshot.h"
#include "ViewGrid.h"
#include "Common/Macro/AllMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "ServerLogics/ServerLogic.h"

namespace GameLogic
{
	ViewSnapshot::ViewSnapshot()
	{

	}

	void ViewSnapshot::Reset()
	{
		view_grids.clear();
		scene_units.clear();
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

		 for (auto so : scene_units)
		 {
			 if (other->scene_units.count(so.first) <= 0)
			 {
				 diff.more_su.insert(so);
			 }
		 }
		 for (auto so : other->scene_units)
		 {
			 if (scene_units.count(so.first) <= 0)
			 {
				 diff.miss_su.insert(so);
			 }
		 }

		 return diff;
	}

	bool ViewSnapshot::CanSeeSu(uint64_t su_id)
	{
		return scene_units.count(su_id) > 0;
	}

	ViewSnapshotDifference::ViewSnapshotDifference()
	{
			
	}

	void ViewSnapshotDifference::Reset()
	{
		more_view_grids.clear();
		miss_view_grids.clear();
		miss_su.clear();
		more_su.clear();
	}

	//////////////////////////////////////////////////////////////////////////


	void ViewSnapshotDifference::PrintLog()
	{
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT,
			"-----------------------------------------------------------------------------");
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference miss_scene_objs {0}", miss_su.size());
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference more_scene_objs {0}", more_su.size());
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference miss_view_grids {0}", miss_view_grids.size());
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT,
			"ViewSnapshotDifference more_view_grids {0}", more_view_grids.size());
	}
}