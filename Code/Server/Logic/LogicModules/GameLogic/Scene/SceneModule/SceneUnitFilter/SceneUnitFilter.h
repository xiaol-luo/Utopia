#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Common/Geometry/GeometryDefine.h"
#include "SceneUnitQTree.h"
#include <vector>
#include <array>

namespace GameLogic
{
	enum ESceneUnitFilterWay
	{
		ESceneUnitFilterWay_ExculdeSuids,
		ESceneUnitFilterWay_UnitType,
		ESceneUnitFilterWay_Relation,
		ESceneUnitFilterWay_ShapeCircle,
		ESceneUnitFilterWay_ShapeObb2,
		ESceneUnitFilterWay_ShapeSector,
		ESceneUnitFilterWay_LimitNum,
		ESceneUnitFilterWay_Count,
	};

	struct SceneUnitFilterWayParams
	{
		SceneUnitFilterWayParams()
		{

		}

		std::array<bool, ESceneUnitFilterWay_Count> is_active = { false };

		EffectFilterShape shape;
		AABB2 cached_shape_aabb;

		struct _exclude_suids
		{
			std::unordered_set<uint64_t> excludeSuids;
		} exclude_suids;

		struct _relations
		{
			std::shared_ptr<SceneUnit> caster;
			int relations;
		} relations;

		struct _shape_obb2
		{
			OBB2 oob2;
		} shape_obb2;

		struct _shape_circle
		{
			Circle circle;
		} shape_circle;
		
		struct _shape_sector
		{
			Sector sector;
		} shape_sector;

		struct _limit_num
		{
			int num;
			EEffectFilterLimitNumPriority priority;
		} limit_num;

		struct _unit_type
		{
			int64_t allow_types;
		} unit_type;

		void CalShape();
	};

	class SceneUnitFilter : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE/* = ESceneModule_UnitFilter*/;
	public:
		SceneUnitFilter();
		virtual ~SceneUnitFilter() override;

	public:
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FindSceneUnit(const SceneUnitFilterWayParams &params);
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> ExtractSceneUnit(const SceneUnitFilterWayParams &params, const std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &sus);
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> ExtractSceneUnit(const SceneUnitFilterWayParams &params, const std::vector<std::shared_ptr<SceneUnit> > &sus);

	protected:
		using FilterWay = void(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		std::array<FilterWay *, ESceneUnitFilterWay_Count> m_filter_way;
		void ExtraFilterProcess(const SceneUnitFilterWayParams &params, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);

		static void FilterUnitType(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterExcludeSuids(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterRelation(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterShapeObb2(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterShapeCircle(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterShapeSector(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterLimitNum(const SceneUnitFilterWayParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);

	protected:
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FindUnits(AABB2 rect);
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FindUnits(OBB2 obb);
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FindUnits(Circle circle);
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FindUnits(Sector sector);
		void FindUnits(AABB2 rect, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &out_ret);

	protected:
		virtual bool OnAwake() override;
		virtual void OnUpdate() override;

		SceneUnitQTree m_qtree;
		std::unordered_map<uint64_t, SceneUnitQTreeNodeUnit *> m_id_unit_map;
		void OnSceneUnitEnterScene(std::shared_ptr<SceneUnit> su);
		void OnSceneUnitLeaveScene(std::shared_ptr<SceneUnit> su);
		void OnSceneUnitPosChange(std::shared_ptr<SceneUnit> su, Vector3 old_pos, Vector3 new_pos);
	};
}
