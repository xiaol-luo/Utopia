#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Common/Geometry/GeometryDefine.h"
#include "SceneUnitQTree.h"

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
		std::unordered_set<std::shared_ptr<SceneUnit>> FilterSceneUnit(EffectFilterOption filter_option);

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
