#include "MoveObject.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"

namespace GameLogic
{
	MoveObject::MoveObject(ESceneObjectType obj_type) : SceneObject(obj_type)
	{

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

	void MoveObject::SetSpeed(float speed)
	{
		m_speed = speed;
		m_scene->MoveMgr()->SetMaxSpeed(m_nav_agent_id, speed);
	}

	void MoveObject::SetVelocity(Vector3 val)
	{
		m_velocity = val;
	}

	void MoveObject::TryMoveToPos(const Vector3 &pos)
	{
		m_scene->MoveMgr()->TryMoveToPos(m_nav_agent_id, pos);
	}

	void MoveObject::TryMoveToDir(float angle)
	{
		m_scene->MoveMgr()->TryMoveToDir(m_nav_agent_id, angle);
	}

	void MoveObject::TryStopMove()
	{
		m_scene->MoveMgr()->StopMove(m_nav_agent_id);
	}

	EMoveType MoveObject::GetMoveType()
	{
		return EMoveType();
	}

	Vector3 MoveObject::GetDesiredMovePos()
	{
		return Vector3();
	}

	Vector3 MoveObject::GetForceMovePos()
	{
		return Vector3();
	}
}

