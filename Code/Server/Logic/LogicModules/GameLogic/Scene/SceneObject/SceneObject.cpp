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

	void SceneObject::SetPos(const Vector3 & val)
	{
		if (val == m_pos)
			return;

		Vector3 old_pos = m_pos;
		m_pos = val;
		this->OnPosChange(old_pos);
	}

	void SceneObject::SetRotation(float val)
	{
		if (abs(val - m_rotation) < FLT_EPSILON)
			return;

		float old_val = m_rotation;
		m_rotation = val;
		this->OnRotationChange(old_val);
	}

	void SceneObject::SyncClient(uint64_t uid, bool is_all)
	{

	}

	void SceneObject::OnPosChange(const Vector3 &old_val)
	{

	}

	void SceneObject::OnRotationChange(float old_val)
	{
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