#include "SceneUnitFilter.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include <memory>
#include <functional>
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"

namespace GameLogic
{
	SceneUnitFilter::SceneUnitFilter() : SceneModule(MODULE_TYPE)
	{

	}

	SceneUnitFilter::~SceneUnitFilter()
	{

	}

	std::unordered_set<std::shared_ptr<SceneUnit>> SceneUnitFilter::FilterSceneUnit(EffectFilterOption filter_option)
	{
		std::unordered_set<std::shared_ptr<SceneUnit>> ret_sus = std::unordered_set<std::shared_ptr<SceneUnit>>();


		return ret_sus;
	}

	bool SceneUnitFilter::OnAwake()
	{
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

	}

	void SceneUnitFilter::OnSceneUnitLeaveScene(std::shared_ptr<SceneUnit> su)
	{

	}
	void SceneUnitFilter::OnSceneUnitPosChange(std::shared_ptr<SceneUnit> su, Vector3 old_pos, Vector3 new_pos)
	{
	}
}
