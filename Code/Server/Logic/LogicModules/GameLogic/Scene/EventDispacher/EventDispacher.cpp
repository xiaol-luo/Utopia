#include "EventDispacher.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "GameLogic/Scene/SceneObject/MoveObject.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/ViewMgr/ViewMgr.h"

namespace GameLogic
{
	SceneEventDispacher::SceneEventDispacher(Scene * scene)
	{
		m_scene = scene;
	}

	SceneEventDispacher::~SceneEventDispacher()
	{

	}

	void SceneEventDispacher::OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{
		scene_obj->OnEnterScene(m_scene);
		m_scene->GetViewMgr()->OnAddSceneObject(scene_obj);
		std::shared_ptr<MoveObject> move_ptr = std::dynamic_pointer_cast<MoveObject>(scene_obj);
		if (nullptr != move_ptr)
		{
			m_scene->GetMoveMgr()->OnMoveObjectEnterScene(move_ptr);
		}

	}
	void SceneEventDispacher::OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{
		scene_obj->OnLeaveScene(m_scene);
		m_scene->GetViewMgr()->OnRemoveSceneObject(scene_obj);
		std::shared_ptr<MoveObject> move_ptr = std::dynamic_pointer_cast<MoveObject>(scene_obj);
		if (nullptr != move_ptr)
		{
			m_scene->GetMoveMgr()->OnMoveObjectLeaveScene(move_ptr);
		}
	}
	void SceneEventDispacher::OnMoveObjectMoveAgentStateChange(std::shared_ptr<MoveObject> move_obj)
	{
	}
	void SceneEventDispacher::OnMoveObjectVelocityChange(std::shared_ptr<MoveObject> move_obj)
	{
	}
	void SceneEventDispacher::OnSceneObjectPosChange(std::shared_ptr<SceneObject> move_obj)
	{
	}
}