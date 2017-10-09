#include "MoveObject.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

namespace GameLogic
{
	MoveObject::MoveObject(ESceneObjectType obj_type) : SceneObject(obj_type)
	{
		m_navAgent = new NavAgent();
	}

	MoveObject::~MoveObject()
	{

	}
	void MoveObject::OnEnterScene(Scene * scene)
	{
		SceneObject::OnLeaveScene(scene);
	}
	void MoveObject::OnLeaveScene(Scene * scene)
	{
		SceneObject::OnLeaveScene(scene);
	}
	void MoveObject::Update(long long now_ms)
	{
		SceneObject::Update(now_ms);
	}
}

