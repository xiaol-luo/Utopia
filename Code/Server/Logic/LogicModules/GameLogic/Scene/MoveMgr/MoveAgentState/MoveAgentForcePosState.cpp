#include "MoveAgentForcePosState.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "Common/Macro/ServerLogicMacro.h"

GameLogic::MoveAgentForcePosState::MoveAgentForcePosState(MoveAgent * move_agent) : MoveAgentState(move_agent, NetProto::EMoveAgentState_ForcePos)
{

}

GameLogic::MoveAgentForcePosState::~MoveAgentForcePosState()
{

}

void GameLogic::MoveAgentForcePosState::Enter(void * param)
{
	m_move_agent->NavDisable();
	m_move_agent->SetVelocity(CalNextVolecity());
	m_is_done = false;
}

void GameLogic::MoveAgentForcePosState::Exit()
{

}

void GameLogic::MoveAgentForcePosState::Update(long deltaMs)
{
	if (m_is_done)
		return;

	Vector3 curr_pos = m_move_agent->GetPos();
	if ((m_destination - curr_pos).sqrMagnitude() < FLT_MIN)
	{
		m_is_done = true;
		return;
	}

	// cal pos
	Vector3 move_dir = m_destination - curr_pos;
	move_dir.y = 0;
	move_dir.normalize();
	float delta_time = deltaMs * 1.0 / ITimerModule::MS_PER_SEC;
	Vector3 next_pos = curr_pos + move_dir * m_speed * delta_time;
	{
		Vector3 nor1 = move_dir;
		Vector3 nor2 = next_pos - m_destination; // 获得从m_destination指向next_pos的向量
		nor1.y = 0; nor2.y = 0;
		nor1.normalize(); nor2.normalize();
		if (Vector3::dot(nor1, nor2) > 0) // 夹角小于90度，也即ret_pos越过了m_hit_pos
		{
			next_pos = m_destination;
			m_is_done = true;
		}
	}
	m_move_agent->SetPos(next_pos);
	m_move_agent->SetVelocity(CalNextVolecity());	
}

void GameLogic::MoveAgentForcePosState::ForcePos(const Vector3 &destination, float speed)
{
	m_speed = speed;
	dtPolyRef poly_ref;
	if (!m_move_agent->GetMoveMgr()->GetNavMesh()->FindNearestPoint(destination, poly_ref, m_destination))
	{
		m_destination = m_move_agent->GetPos();
	}
}

void GameLogic::MoveAgentForcePosState::ForcePos(const Vector3 &destination)
{
	this->ForcePos(destination, m_speed);
}

const Vector3 GameLogic::MoveAgentForcePosState::CalNextVolecity()
{
	Vector3 next_move_dir = m_destination - m_move_agent->GetPos();
	next_move_dir.y = 0;
	next_move_dir.normalize();
	Vector3 next_velocity = next_move_dir * m_speed;
	return next_velocity;
}


