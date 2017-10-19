#include "MoveAgentMoveToDirState.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

GameLogic::MoveAgentMoveToDirState::MoveAgentMoveToDirState(MoveAgent * move_agent) : MoveAgentState(move_agent, EMoveAgentState_MoveToDir)
{

}

GameLogic::MoveAgentMoveToDirState::~MoveAgentMoveToDirState()
{

}

void GameLogic::MoveAgentMoveToDirState::Enter(void * param)
{
	m_move_agent->SetVelocity(Vector3::zero);
	NavAgent *agent = m_move_agent->GetNavAgent();
	agent->SetPos(m_move_agent->GetPos());
	agent->TryMoveToDir(m_desired_dir);
	agent->Enable();
}

void GameLogic::MoveAgentMoveToDirState::Exit()
{
	m_move_agent->GetNavAgent()->StopMove();
}

void GameLogic::MoveAgentMoveToDirState::Update(long deltaMs)
{
	m_move_agent->GetNavAgent()->OnMoved();
}

void GameLogic::MoveAgentMoveToDirState::Flash(const Vector3 & val)
{
	m_move_agent->GetNavAgent()->SetPos(val);
}

void GameLogic::MoveAgentMoveToDirState::SetDesiredDir(float dir)
{
	m_desired_dir = dir;
}

