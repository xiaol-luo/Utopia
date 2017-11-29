#include "ViewDefine.h"

namespace GameLogic
{
	struct ViewGrid;
	class SceneUnit;

	struct ViewSnapshotDifference
	{
		ViewSnapshotDifference();
		void Reset();

		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> miss_scene_objs;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> more_scene_objs;

		std::unordered_map<uint64_t, std::weak_ptr<SceneUnit>> miss_su;
		std::unordered_map<uint64_t, std::weak_ptr<SceneUnit>> more_su;

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
		bool CanSeeSu(uint64_t su_id);

		ViewGridVec view_grids;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> scene_objs;
		std::unordered_map < uint64_t, std::weak_ptr<SceneUnit>> scene_units;
	};
}
