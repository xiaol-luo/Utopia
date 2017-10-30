#include "MoveAgentIdleState.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

GameLogic::MoveAgentIdleState::MoveAgentIdleState(MoveAgent * move_agent) : MoveAgentState(move_agent, NetProto::EMoveAgentState_Idle)
{

}

GameLogic::MoveAgentIdleState::~MoveAgentIdleState()
{

}

void GameLogic::MoveAgentIdleState::Enter(void * param)
{
	m_move_agent->GetNavAgent()->StopMove();
	m_move_agent->GetNavAgent()->Enable();
	m_move_agent->SetVelocity(Vector3::zero);
}

void GameLogic::MoveAgentIdleState::Exit()
{

}

void GameLogic::MoveAgentIdleState::Update(long deltaMs)
{

}

