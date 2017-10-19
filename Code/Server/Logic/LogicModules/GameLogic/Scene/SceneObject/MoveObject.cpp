#include "MoveObject.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Utils/LogUtil.h"

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
		if (nullptr != m_move_agent)
			m_move_agent->SetMoveMaxSpeed(m_speed);
	}

	const Vector3 & MoveObject::GetVelocity()
	{
		if (m_move_agent)
			return m_move_agent->GetVelocity();
		return Vector3::zero;
	}

	void MoveObject::TryMoveToPos(const Vector3 &pos)
	{
		if (m_move_agent)
			m_move_agent->TryMoveToPos(pos);
	}

	void MoveObject::TryMoveToDir(float angle)
	{
		if (m_move_agent)
			m_move_agent->TryMoveToDir(angle);
	}

	void MoveObject::CancelMove()
	{
		if (m_move_agent)
			m_move_agent->CancelMove();
	}

	void MoveObject::CancelForceMove()
	{
		if (m_move_agent)
			m_move_agent->CancelForceMove();
	}

	void MoveObject::ForceMoveLine(const Vector2 & dir, float speed, float time_sec, bool ignore_terrian)
	{
		if (m_move_agent)
			m_move_agent->ForceMoveLine(dir, speed, time_sec, ignore_terrian);
	}

	void MoveObject::Immobilized(long ms)
	{
		if (m_move_agent)
			m_move_agent->Immobilized(ms);
	}

	void MoveObject::CancelImmobilized()
	{
		if (m_move_agent)
			m_move_agent->CancelImmobilized();
	}

	void MoveObject::Flash(const Vector3 & val)
	{
		if (m_move_agent)
			m_move_agent->Flash(val);
	}

	EMoveAgentState MoveObject::GetMoveAgentState()
	{
		return m_move_agent->GetMoveAgentState();
	}

	void MoveObject::OnMoveStateChange(std::weak_ptr<MoveObject> obj, MoveAgent * agent, EMoveAgentState old_state)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		LogUtil::Debug(LogModule::LOGGER_ID_STDOUT + 2, "MoveStateChange:{0}->{1}", old_state, agent->GetMoveAgentState());
	}

	void MoveObject::OnPostChange(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_pos)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		ptr->SetPos(agent->GetPos());
		Vector3 pos = agent->GetPos();
		LogUtil::Debug(LogModule::LOGGER_ID_STDOUT + 2, "OnPostChange:{:3.2f}, {:3.2f}, {:3.2f}", pos.x, pos.y, pos.z);
	}

	void MoveObject::OnVelocityChange(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_velocity)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		// LogUtil::Debug(LogModule::LOGGER_ID_STDOUT, "MoveStateChange:{0}->{1}", old_state, agent->GetMoveAgentState());
	}
}

