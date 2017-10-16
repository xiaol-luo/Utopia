#include "MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentIdleState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentMoveToPosState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentMoveToDirState.h"

GameLogic::EMoveState GameLogic::MoveAgent::CalMoveState(GameLogic::EMoveAgentState state)
{
	EMoveState ret = EMoveState_Idle;
	switch (state)
	{
	case EMoveAgentState_Idle:
		ret = EMoveState_Idle;
		break;
	case EMoveAgentState_MoveToDir:
	case EMoveAgentState_MoveToPos:
		ret = EMoveState_Move;
		break;
	case EMoveAgentState_ForceLine:
	case EMoveAgentState_ForceSky:
		ret = EMoveState_ForceMove;
		break;
	case EMoveAgentState_Immobilized:
		ret = EMoveState_Immobilized;
		break;
	}

	return ret;
}

GameLogic::MoveAgent::MoveAgent(MoveMgr * move_mgr) : m_move_mgr(move_mgr)
{
	m_nav_agent = new NavAgent(move_mgr->GetNavMesh());
	m_nav_agent->SetMovedCb(std::bind(&GameLogic::MoveAgent::OnNavAgentMoved, this, std::placeholders::_1));

	m_states[EMoveAgentState_Idle] = new MoveAgentIdleState(this);
	m_states[EMoveAgentState_MoveToDir] = new MoveAgentMoveToDirState(this);
	m_states[EMoveAgentState_MoveToPos] = new MoveAgentMoveToPosState(this);
	m_next_state = m_states[EMoveState_Idle];
	m_curr_state = m_states[EMoveState_Idle];
}

GameLogic::MoveAgent::~MoveAgent()
{
	for (int i = 0; i < EMoveAgentState_Max; ++i)
	{
		delete m_states[i]; m_states[i] = nullptr;
	}
}

GameLogic::EMoveAgentState GameLogic::MoveAgent::GetMoveAgentState()
{
	return m_curr_state->GetState();
}

GameLogic::EMoveState GameLogic::MoveAgent::GetMoveState()
{
	return CalMoveState(this->GetMoveAgentState());
}

void GameLogic::MoveAgent::SetPos(Vector3 val)
{
	Vector3 old_pos = m_pos;
	m_pos = val;
	if (m_event_cb.post_change_cb)
		m_event_cb.post_change_cb(this, old_pos);
}

void GameLogic::MoveAgent::SetVelocity(const Vector3 &val)
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

void GameLogic::MoveAgent::OnNavAgentMoved(NavAgent * agent)
{
	this->SetPos(agent->GetPos());
	this->SetVelocity(agent->GetVelocity());
}

void GameLogic::MoveAgent::Update(long deltaMs)
{
	m_curr_state->Update(deltaMs);
}

void GameLogic::MoveAgent::TryMoveToPos(const Vector3 &pos)
{

}

void GameLogic::MoveAgent::TryMoveToDir(float angle)
{

}

void GameLogic::MoveAgent::StopMove()
{

}

void GameLogic::MoveAgent::TryResumeMove()
{

}

