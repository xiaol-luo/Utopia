#include "MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentIdleState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentMoveToPosState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentMoveToDirState.h"

GameLogic::MoveAgent::MoveAgent(MoveMgr * move_mgr) : m_move_mgr(move_mgr)
{
	m_nav_agent = new NavAgent(move_mgr->GetNavMesh());

	m_states[EMoveAgentState_Idle] = new MoveAgentIdleState(this);
	m_states[EMoveAgentState_MoveToDir] = new MoveAgentMoveToDirState(this);
	m_states[EMoveAgentState_MoveToPos] = new MoveAgentMoveToPosState(this);
}

GameLogic::MoveAgent::~MoveAgent()
{
	for (int i = 0; i < EMoveAgentState_Max; ++i)
	{
		delete m_states[i]; m_states[i] = nullptr;
	}
}

void GameLogic::MoveAgent::SetPos(Vector3 val)
{
	Vector3 old_pos = m_pos;
	m_pos = val;
	if (m_event_cb.post_change_cb)
		m_event_cb.post_change_cb(this, old_pos);
}

void GameLogic::MoveAgent::SetVelocity(Vector3 val)
{
	Vector3 old_velocity = m_velocity;
	m_velocity = val;
	if (nullptr != m_event_cb.velocity_change_cb)
		m_event_cb.velocity_change_cb(this, val);
}

float GameLogic::MoveAgent::GetMoveMaxSpeed()
{
	return m_nav_agent->GetMaxSpeed();
}

void GameLogic::MoveAgent::SetMoveMaxSpeed(float val)
{
	m_nav_agent->SetMaxSpeed(val);
}

