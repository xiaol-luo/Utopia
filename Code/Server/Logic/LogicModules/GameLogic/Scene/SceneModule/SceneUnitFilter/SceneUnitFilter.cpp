#include "SceneUnitFilter.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include <memory>
#include <functional>
#include "GameLogic/Scene/Defines/ESceneEvent.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/NewScene.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	const ESceneModule SceneUnitFilter::MODULE_TYPE = ESceneModule_UnitFilter;

	SceneUnitFilter::SceneUnitFilter() : SceneModule(MODULE_TYPE)
	{
		m_filter_way[ESceneUnitFilterWay_ExculdeSuids] = &SceneUnitFilter::FilterExcludeSuids;
		m_filter_way[ESceneUnitFilterWay_Relation] = &SceneUnitFilter::FilterRelation;
		m_filter_way[ESceneUnitFilterWay_ShapeObb2] = &SceneUnitFilter::FilterShapeObb2;
		m_filter_way[ESceneUnitFilterWay_ShapeCircle] = &SceneUnitFilter::FilterShapeCircle;
		m_filter_way[ESceneUnitFilterWay_ShapeSector] = &SceneUnitFilter::FilterShapeSector;
		m_filter_way[ESceneUnitFilterWay_LimitNum] = &SceneUnitFilter::FilterLimitNum;
		m_filter_way[ESceneUnitFilterWay_UnitType] = &SceneUnitFilter::FilterUnitType;
	}

	SceneUnitFilter::~SceneUnitFilter()
	{
		m_qtree.Release();
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::FindSceneUnit(const ESceneUnitFilterWayParams & params)
	{
		ESceneUnitFilterWayParams tmp_param = params;
		tmp_param.CalShape();
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> out_ret;
		this->FindUnits(tmp_param.cached_shape_aabb, out_ret);
		ExtraFilterProcess(tmp_param, out_ret);
		return out_ret;
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::ExtractSceneUnit(const ESceneUnitFilterWayParams &params, const std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& sus)
	{
		ESceneUnitFilterWayParams tmp_param = params;
		tmp_param.CalShape();
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> out_ret(sus.begin(), sus.end());
		ExtraFilterProcess(tmp_param, out_ret);
		return out_ret;
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::ExtractSceneUnit(const ESceneUnitFilterWayParams &params, const std::vector<std::shared_ptr<SceneUnit> >& sus)
	{
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> su_map;
		for (auto su : sus)
		{
			if (nullptr == su)
				continue;

			su_map.insert_or_assign(su->GetId(), su);
		}
		return std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>();
	}

	void SceneUnitFilter::ExtraFilterProcess(const ESceneUnitFilterWayParams & params, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		for (int i = 0; i < ESceneUnitFilterWay_Count; ++i)
		{
			if (params.is_active[i])
			{
				m_filter_way[i](params, units);
			}
		}
	}

	void SceneUnitFilter::FilterUnitType(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		int64_t allow_types = param.unit_type.allow_types;
		for (auto it = units.begin(); it != units.end();)
		{
			NetProto::ESceneUnitType unit_type = it->second->GetUnitType();
			if (allow_types & ((int64_t)1 << unit_type))
				++it;
			else
				it = units.erase(it);
		}
	}

	void SceneUnitFilter::FilterExcludeSuids(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		for (uint64_t suid : param.exclude_suids.excludeSuids)
		{
			units.erase(suid);
		}
	}

	void SceneUnitFilter::FilterRelation(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		int allowRelation = param.relations.relations;
		std::shared_ptr<SceneUnit> caster = param.relations.caster;
		if (nullptr == caster)
			return;

		std::vector<uint64_t> unfitSuids;
		for (auto kv_pair : units)
		{
			NetProto::ESceneUnitRelation esur = caster->GetScene()->SceneUnitRelation(caster, kv_pair.second);
			if(!(allowRelation & (1 << esur)))
			{
				unfitSuids.push_back(kv_pair.first);
			}
		}
		for (uint64_t suid : unfitSuids)
		{
			units.erase(suid);
		}
	}

	void SceneUnitFilter::FilterShapeObb2(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		OBB2 obb2 = param.shape_obb2.oob2;
		for (auto it = units.begin(); it != units.end();)
		{
			uint64_t id = it->first;
			std::shared_ptr<SceneUnitBody> su_body = it->second->GetModule<SceneUnitBody>();
			bool is_intersect = false;

			switch (su_body->GetEShape())
			{
			case ESceneObjectShape_Circle:
			{
				is_intersect = GeometryUtils::IsIntersectCircleOBB2(su_body->GetShapeCircle(), obb2);
			}
			break;
			case ESceneObjectShape_Rect:
			{
				is_intersect = GeometryUtils::IsIntersectObb2(su_body->GetShapeObb2(), obb2);
			}
			break;
			default:
				break;
			}
			if (is_intersect)
				++it;
			else
				it = units.erase(it);
		}
	}

	void SceneUnitFilter::FilterShapeCircle(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		Circle circle = param.shape_circle.circle;
		for (auto it = units.begin(); it != units.end();)
		{
			uint64_t id = it->first;
			std::shared_ptr<SceneUnitBody> su_body = it->second->GetModule<SceneUnitBody>();
			bool is_intersect = false;

			switch (su_body->GetEShape())
			{
			case ESceneObjectShape_Circle:
			{
				is_intersect = GeometryUtils::IsIntersectCircle(su_body->GetShapeCircle(), circle);
			}
			break;
			case ESceneObjectShape_Rect:
			{
				is_intersect = GeometryUtils::IsIntersectCircleOBB2(circle, su_body->GetShapeObb2());
			}
			break;
			default:
				break;
			}
			if (is_intersect)
				++it;
			else
				it = units.erase(it);
		}
	}

	void SceneUnitFilter::FilterShapeSector(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		Sector sector = param.shape_sector.sector;
		for (auto it = units.begin(); it != units.end();)
		{
			uint64_t id = it->first;
			std::shared_ptr<SceneUnitBody> su_body = it->second->GetModule<SceneUnitBody>();
			bool is_intersect = false;

			switch (su_body->GetEShape())
			{
			case ESceneObjectShape_Circle:
			{
				is_intersect = GeometryUtils::IsIntersectCircleSector(su_body->GetShapeCircle(), sector);
			}
			break;
			case ESceneObjectShape_Rect:
			{
				is_intersect = GeometryUtils::IsIntersectObb2Sector(su_body->GetShapeObb2(), sector);
			}
			break;
			default:
				break;
			}
			if (is_intersect)
				++it;
			else
				it = units.erase(it);
		}
	}

	void SceneUnitFilter::FilterLimitNum(const ESceneUnitFilterWayParams & param, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& units)
	{
		while ((int)units.size() > param.limit_num.num)
		{
			units.erase(units.begin());
		}
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::FindUnits(AABB2 rect)
	{
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> ret_sus;
		this->FindUnits(rect, ret_sus);
		return std::move(ret_sus);
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::FindUnits(OBB2 obb)
	{
		AABB2 rect = GeometryUtils::BuildAABB2(obb);
		return std::move(this->FindUnits(rect));
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::FindUnits(Circle circle)
	{
		AABB2 rect = GeometryUtils::BuildAABB2(circle);
		return std::move(this->FindUnits(rect));
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> SceneUnitFilter::FindUnits(Sector sector)
	{
		AABB2 rect = GeometryUtils::BuildAABB2(sector);
		return std::move(this->FindUnits(rect));
	}

	void SceneUnitFilter::FindUnits(AABB2 rect, std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>>& out_ret)
	{
		std::unordered_set<SceneUnitQTreeNodeUnit *> node_units;
		m_qtree.FindUnits(rect, node_units);
		for (SceneUnitQTreeNodeUnit *node_unit : node_units)
		{
			auto unit = node_unit->unit.lock();
			out_ret[unit->GetId()] = unit;
		}
	}

	bool SceneUnitFilter::OnAwake()
	{
		AABB2 area = m_scene->GetModule<SceneNavMesh>()->GetNavMesh()->GetArea();
		m_qtree.Init(area);

		this->GetSceneEvProxy()->Subscribe<std::shared_ptr<SceneUnit>>(ESU_EnterScene,
			std::bind(&SceneUnitFilter::OnSceneUnitEnterScene, this, std::placeholders::_1));
		this->GetSceneEvProxy()->Subscribe<std::shared_ptr<SceneUnit>>(ESU_LeaveScene,
			std::bind(&SceneUnitFilter::OnSceneUnitLeaveScene, this, std::placeholders::_1));
		this->GetSceneEvProxy()->Subscribe<std::shared_ptr<SceneUnit>, Vector3, Vector3>(ESU_PosChange,
			std::bind(&SceneUnitFilter::OnSceneUnitPosChange, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		return true;
	}

	void SceneUnitFilter::OnUpdate()
	{
	}

	void SceneUnitFilter::OnSceneUnitEnterScene(std::shared_ptr<SceneUnit> su)
	{
		if (m_id_unit_map.count(su->GetId()) > 0)
			return;
		std::shared_ptr<SceneUnitBody> su_body = su->GetModule<SceneUnitBody>();
		if (nullptr == su_body)
			return;

		SceneUnitQTreeNodeUnit *unit_node = new SceneUnitQTreeNodeUnit();
		unit_node->unit = su;
		m_id_unit_map.insert(std::make_pair(su->GetId(), unit_node));

		m_qtree.UpdateNodeUnit(unit_node);
	}

	void SceneUnitFilter::OnSceneUnitLeaveScene(std::shared_ptr<SceneUnit> su)
	{
		auto it = m_id_unit_map.find(su->GetId());
		if (m_id_unit_map.end() != it)
		{
			SceneUnitQTreeNodeUnit *unit_node = it->second;
			unit_node->Deattach();
			delete unit_node;
			m_id_unit_map.erase(it);
		}
	}

	void SceneUnitFilter::OnSceneUnitPosChange(std::shared_ptr<SceneUnit> su, Vector3 new_pos, Vector3 old_pos)
	{
		SceneUnitQTreeNodeUnit *unit_node = nullptr;
		{
			auto it = m_id_unit_map.find(su->GetId());
			if (m_id_unit_map.end() != it)
			{
				unit_node = it->second;
			}
		}
		if (nullptr != unit_node)
		{
			m_qtree.UpdateNodeUnit(unit_node);
		}		
	}
	void ESceneUnitFilterWayParams::CalShape()
	{
		is_active[ESceneUnitFilterWay_ShapeCircle] = false;
		is_active[ESceneUnitFilterWay_ShapeObb2] = false;
		is_active[ESceneUnitFilterWay_ShapeSector] = false;
		cached_shape_aabb.Reset();

		switch (shape.shape)
		{
		case EEffectFilterShape_Circle:
		{
			is_active[ESceneUnitFilterWay_ShapeCircle] = true;
			shape_circle.circle.center = shape.pos;
			shape_circle.circle.radius = shape.shape_param.circle.radius;
			cached_shape_aabb = GeometryUtils::BuildAABB2(shape_circle.circle);
		}
		break;
		case EEffectFilterShape_Rect:
		{
			is_active[ESceneUnitFilterWay_ShapeObb2] = true;
			shape_obb2.oob2.center = shape.pos;
			shape_obb2.oob2.y_axis_dir = shape.dir;
			shape_obb2.oob2.x_half_size = shape.shape_param.rect.x_size;
			shape_obb2.oob2.y_half_size = shape.shape_param.rect.y_size;
			cached_shape_aabb = GeometryUtils::BuildAABB2(shape_obb2.oob2);
		}
		break;
		case EEffectFilterShape_Sector:
		{
			is_active[ESceneUnitFilterWay_ShapeSector] = true;
			shape_sector.sector.center = shape.pos;
			shape_sector.sector.y_axis_dir = shape.dir;
			shape_sector.sector.radius = shape.shape_param.sector.radius;
			shape_sector.sector.halfAngle = shape.shape_param.sector.angle / 2;
			cached_shape_aabb = GeometryUtils::BuildAABB2(shape_sector.sector);
		}
		break;
		}
	}
}
