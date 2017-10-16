#include "MoveObject.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

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
		m_move_agent->SetMoveMaxSpeed(speed);
	}

	const Vector3 & MoveObject::GetVelocity()
	{
		return m_move_agent->GetVelocity();
	}

	void MoveObject::TryMoveToPos(const Vector3 &pos)
	{
		m_move_agent->GetNavAgent()->TryMoveToPos(pos);
	}

	void MoveObject::TryMoveToDir(float angle)
	{
		m_move_agent->GetNavAgent()->TryMoveToDir(angle);
	}

	void MoveObject::TryStopMove()
	{
		m_move_agent->GetNavAgent()->StopMove();
	}

	EMoveAgentState MoveObject::GetMoveAgentState()
	{
		return m_move_agent->GetMoveAgentState();
	}

	Vector3 MoveObject::GetDesiredMovePos()
	{
		return Vector3();
	}

	Vector3 MoveObject::GetForceMovePos()
	{
		return Vector3();
	}

	void MoveObject::OnMoveStateChange(std::weak_ptr<MoveObject> obj, MoveAgent * agent, EMoveAgentState old_state)
	{

	}

	void MoveObject::OnPostChange(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_pos)
	{

	}

	void MoveObject::OnVelocityChange(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_velocity)
	{

	}
}

