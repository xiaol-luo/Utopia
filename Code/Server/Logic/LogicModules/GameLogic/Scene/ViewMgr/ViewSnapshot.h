#include "ViewDefine.h"

namespace GameLogic
{
	struct ViewGrid;

	struct ViewSnapshotDifference
	{
		ViewSnapshotDifference();
		~ViewSnapshotDifference();
		void Reset();

		std::vector<std::weak_ptr<SceneObject>> miss_scene_objs;
		std::vector<std::weak_ptr<SceneObject>> more_scene_objs;
		ViewGridVec miss_view_grids;
		ViewGridVec more_view_grids;
	};

	struct ViewSnapshot
	{
		ViewSnapshot();
		~ViewSnapshot();
		void Reset();
		// other make some opera according "ViewSnapshotDifference" with equal to 'this'
		ViewSnapshotDifference CalDifference(const ViewSnapshot *other); 

		ViewGridVec view_grids;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> scene_objs;
	};
}
