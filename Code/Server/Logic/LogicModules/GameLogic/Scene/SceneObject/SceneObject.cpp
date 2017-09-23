#include "SceneObject.h"
#include "GameLogic/Scene/Scene.h"


namespace GameLogic
{
	SceneObject::SceneObject(ESceneObjectType obj_type) : m_scene(nullptr), m_id(Scene::INVALID_SCENE_OBJID), m_obj_type(obj_type)
	{
	}

	SceneObject::~SceneObject()
	{

	}

	void SceneObject::LeaveScene()
	{
		if (nullptr != m_scene)
		{
			m_scene->RemoveObject(m_id);
		}
	}

	void SceneObject::OnEnterScene(Scene *scene)
	{

	}

	void SceneObject::OnLeaveScene(Scene *scene)
	{

	}

	void SceneObject::Update(long long now_ms)
	{

	}
}