#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Common/Geometry/GeometryDefine.h"
#include "SceneUnitQTree.h"
#include <vector>

namespace GameLogic
{
	class SceneUnitFilter : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE = ESceneModule_UnitFilter;
	public:
		SceneUnitFilter();
		virtual ~SceneUnitFilter() override;

	public:
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FilterSceneUnit(EffectFilterShape shape);
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FilterSceneUnit(EffectFilterShape shape, std::shared_ptr<SceneUnit> caster, int relation);

	protected:
		enum EFilterWay
		{
			EFilterWay_ExculdeSuids,
			EFilterWay_Relation,
			EFilterWay_Count,
		};

		struct FilterParams
		{
			FilterParams()
			{
				memset(is_active, 0, sizeof(is_active));
			}

			bool is_active[EFilterWay_Count];

			struct
			{
				std::unordered_set<uint64_t> excludeSuids;
			} exclude_suids;
			
			struct
			{
				std::shared_ptr<SceneUnit> caster;
				int relation;
			} relation;
			
		};

		using FilterWay = void(const FilterParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		FilterWay *m_filter_way[EFilterWay_Count];

		static void FilterExcludeSuids(const FilterParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);
		static void FilterRelation(const FilterParams &param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> &units);

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
