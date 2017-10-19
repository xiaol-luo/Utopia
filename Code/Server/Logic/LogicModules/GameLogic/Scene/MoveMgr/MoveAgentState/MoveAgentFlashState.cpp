#include "MoveAgentFlashState.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

GameLogic::MoveAgentFlashState::MoveAgentFlashState(MoveAgent * move_agent) : MoveAgentState(move_agent, EMoveAgentState_Idle)
{

}

GameLogic::MoveAgentFlashState::~MoveAgentFlashState()
{

}

void GameLogic::MoveAgentFlashState::Enter(void * param)
{
	m_move_agent->GetNavAgent()->StopMove();
	m_move_agent->GetNavAgent()->Enable();
}

void GameLogic::MoveAgentFlashState::Exit()
{

}

void GameLogic::MoveAgentFlashState::Update(long deltaMs)
{

}

