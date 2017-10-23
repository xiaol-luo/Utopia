#include "MoveObject.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"

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

	void MoveObject::SetRadius(float radius)
	{
		if (abs(m_radius - radius) < FLT_EPSILON)
			return;

		float old_val = m_radius;
		this->OnRadiusChange(old_val);
	}

	void MoveObject::SetSpeed(float speed)
	{
		if (abs(m_speed - speed) < FLT_EPSILON)
			return;

		float old_val = m_speed;
		m_speed = speed;
		if (nullptr != m_move_agent)
			m_move_agent->SetNavMaxSpeed(m_speed);
		this->OnSpeedChange(old_val);
	}

	void MoveObject::OnSpeedChange(float old_val)
	{

	}

	void MoveObject::OnRadiusChange(float old_val)
	{

	}

	const Vector3 & MoveObject::GetVelocity()
	{
		if (m_move_agent)
			return m_move_agent->GetVelocity();
		return Vector3::zero;
	}

	void MoveObject::OnMoveAgentStateChange(EMoveAgentState old_val)
	{
		m_move_change = true;
	}

	void MoveObject::OnVelocityChange(const Vector3 & old_val)
	{
		m_move_change = true;
	}

	void MoveObject::OnPosChange(const Vector3 & old_val)
	{
		m_move_change = true;
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

	void MoveObject::ForcePos(const Vector3 & destination, float speed)
	{
		if (m_move_agent)
			m_move_agent->ForcePos(destination, speed);
	}

	void MoveObject::ChangeForcePosDestination(const Vector3 & destination)
	{
		if (m_move_agent)
			m_move_agent->ChangeForcePosDestination(destination);
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

	void MoveObject::MoveStateChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent * agent, EMoveAgentState old_state)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		ptr->OnMoveAgentStateChange(old_state);
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT + 2, "MoveStateChange:{0}->{1}", old_state, agent->GetMoveAgentState());
	}

	void MoveObject::PostChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_pos)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		ptr->SetPos(agent->GetPos());
		Vector3 pos = agent->GetPos();
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT + 2, "OnPostChange [{}]:{:3.2f}, {:3.2f}, {:3.2f}", agent->GetMoveAgentState(), pos.x, pos.y, pos.z);
	}

	void MoveObject::VelocityChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_velocity)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		Vector3 velocity = agent->GetVelocity();
		ptr->OnVelocityChange(old_velocity);

		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT + 2, "OnVelocityChange [{}]:{:3.2f}, {:3.2f}, {:3.2f}", agent->GetMoveAgentState(), velocity.x, velocity.y, velocity.z);
	}
}

