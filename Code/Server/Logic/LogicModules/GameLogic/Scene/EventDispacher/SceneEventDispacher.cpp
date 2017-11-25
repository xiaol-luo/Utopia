#include "SceneEventDispacher.h"
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

	void SceneEventDispacher::OnSceneAddObject(std::shared_ptr<SceneObject> scene_obj)
	{
		scene_obj->OnEnterScene(m_scene);
		m_scene->GetViewMgr()->OnAddSceneObject(scene_obj);
		std::shared_ptr<MoveObject> move_ptr = std::dynamic_pointer_cast<MoveObject>(scene_obj);
		if (nullptr != move_ptr)
		{
			m_scene->GetMoveMgr()->OnMoveObjectEnterScene(move_ptr);
		}

	}
	void SceneEventDispacher::OnSceneRemoveObject(std::shared_ptr<SceneObject> scene_obj)
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
	void SceneEventDispacher::OnMoveObjectVelocityChange(std::shared_ptr<MoveObject> move_obj, Vector3 old_velocity)
	{
	}
	void SceneEventDispacher::OnSceneObjectPosChange(std::shared_ptr<SceneObject> scene_obj, Vector3 old_pos)
	{
		m_scene->GetViewMgr()->OnSceneObjectPosChange(scene_obj);
	}
	void SceneEventDispacher::OnSceneObjectFaceDirChange(std::shared_ptr<SceneObject> scene_obj, float old_face_dir)
	{
	}
}