#include "ViewDefine.h"

namespace GameLogic
{
	struct ViewGrid;

	struct ViewSnapshotDifference
	{
		ViewSnapshotDifference();
		void Reset();

		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> miss_scene_objs;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> more_scene_objs;
		ViewGridVec miss_view_grids;
		ViewGridVec more_view_grids;

		void PrintLog();
	};

	struct ViewSnapshot
	{
		ViewSnapshot();
		void Reset();
		// other make some opera according "ViewSnapshotDifference" with equal to 'this'
		ViewSnapshotDifference CalDifference(const ViewSnapshot *other) const; 

		ViewGridVec view_grids;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> scene_objs;
	};
}
