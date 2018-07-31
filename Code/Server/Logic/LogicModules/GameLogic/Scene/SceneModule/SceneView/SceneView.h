#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Defines/ViewDefine.h"
#include <functional>
#include <array>

namespace NetProto
{
	class ViewSnapshot;
	class ViewAllGrids;
}

namespace GameLogic
{
	struct ViewGrid;
	struct ViewSnapshot;
	class SceneUnitSight;
	class SceneUnitBody;
	class SceneUnit;

	class SceneView : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE/*= ESceneModule_View*/;
	public:
		SceneView();
		virtual ~SceneView() override;

		ViewGridVec GetCircleCoverGrids(float center_x, float center_y, float radius);
		ViewGridVec GetAABBConverGrids(float min_x, float min_y, float max_x, float max_y);
		int CalGridIdx(int row, int col);
		bool CalRowCol(int grid_idx, int *row, int *col);
		int InRowIdx(float y);
		int InColIdx(float x);
		int InGridIdx(float x, float y);
		ViewGrid * GetGrid(float x, float y);
		ViewGrid * GetGrid(int grid_id);
		ViewGrid * GetUpGrid(int grid_idx);
		ViewGrid * GetRightGrid(int grid_idx);
		ViewGrid * GetButtomGrid(int grid_idx);
		ViewGrid * GetLeftGrid(int grid_idx);
		std::array<ViewSnapshot *, EViewCamp_Observer> GetSnapshot() { return m_curr_snapshots; }
		std::array<ViewSnapshot *, EViewCamp_Observer> GetPreSnapshot() { return m_pre_snapshots; }
		void MakeSnapshot();
		void FillPbViewSnapshot(EViewCamp camp, NetProto::ViewSnapshot *msg);
		void FillPbViewAllGrids(NetProto::ViewAllGrids * msg);

	protected:
		virtual bool OnAwake() override;
		virtual void OnUpdate() override;
		virtual void OnRelease() override;

	protected:
		bool LoadCfg(std::string file_path);
		float m_grid_edge_length = 0;
		int m_row_num = 0;
		int m_col_num = 0;
		int m_grid_count = 0;
		float m_max_x = 0;
		float m_max_y = 0;
		ViewGrid **m_grids = nullptr;

		std::array<ViewSnapshot *, EViewCamp_Observer> m_curr_snapshots = { nullptr };
		std::array<ViewSnapshot *, EViewCamp_Observer> m_pre_snapshots = { nullptr };

		// ViewSnapshot **m_curr_snapshots = nullptr;
		// ViewSnapshot **m_pre_snapshots = nullptr;

		std::unordered_map<int64_t, std::weak_ptr<SceneUnit>> m_scene_units;
		void OnSceneUnitEnterScene(std::shared_ptr<SceneUnit> su);
		void OnSceneUnitLeaveScene(std::shared_ptr<SceneUnit> su);
	};
}
