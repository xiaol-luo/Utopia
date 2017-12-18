#include "SceneUnitMoveForcePosState.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"

GameLogic::SceneUnitMoveForcePosState::SceneUnitMoveForcePosState(SceneUnitMove * move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_ForcePos)
{

}

GameLogic::SceneUnitMoveForcePosState::~SceneUnitMoveForcePosState()
{

}

void GameLogic::SceneUnitMoveForcePosState::Enter(void * param)
{
	m_move_agent->GetNavAgent()->Disable();
	m_move_agent->SetVelocity(CalNextVolecity());
	m_is_done = false;
}

void GameLogic::SceneUnitMoveForcePosState::Exit()
{

}

void GameLogic::SceneUnitMoveForcePosState::Update(int64_t deltaMs)
{
	if (m_is_done)
		return;

	Vector3 curr_pos = m_move_agent->GetPos();
	if ((m_destination - curr_pos).SqrMagnitude() < FLT_MIN)
	{
		m_is_done = true;
		return;
	}

	// cal pos
	Vector3 move_dir = m_destination - curr_pos;
	move_dir.y = 0;
	move_dir.Normalize();
	float delta_time = deltaMs * 1.0 / ITimerModule::MS_PER_SEC;
	Vector3 next_pos = curr_pos + move_dir * m_speed * delta_time;
	{
		Vector3 nor1 = move_dir;
		Vector3 nor2 = next_pos - m_destination; // 获得从m_destination指向next_pos的向量
		nor1.y = 0; nor2.y = 0;
		nor1.Normalize(); nor2.Normalize();
		if (Vector3::Dot(nor1, nor2) > 0) // 夹角小于90度，也即ret_pos越过了m_hit_pos
		{
			next_pos = m_destination;
			m_is_done = true;
		}
	}
	m_move_agent->SetPos(next_pos);
	m_move_agent->SetVelocity(CalNextVolecity());	
}

void GameLogic::SceneUnitMoveForcePosState::ForcePos(const Vector3 &destination, float speed)
{
	m_speed = speed;
	dtPolyRef poly_ref;
	if (!m_move_agent->GetNavMesh()->FindNearestPoint(destination, poly_ref, m_destination))
	{
		m_destination = m_move_agent->GetPos();
	}
}

void GameLogic::SceneUnitMoveForcePosState::ForcePos(const Vector3 &destination)
{
	this->ForcePos(destination, m_speed);
}

const Vector3 GameLogic::SceneUnitMoveForcePosState::CalNextVolecity()
{
	Vector3 next_move_dir = m_destination - m_move_agent->GetPos();
	next_move_dir.y = 0;
	next_move_dir.Normalize();
	Vector3 next_velocity = next_move_dir * m_speed;
	return next_velocity;
}


