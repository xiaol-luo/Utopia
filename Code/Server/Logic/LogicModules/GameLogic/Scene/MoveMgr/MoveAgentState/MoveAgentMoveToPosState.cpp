#include "MoveAgentMoveToPosState.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Math/Vector3.h"
#include "Common/Math/Vector2.h"

GameLogic::MoveAgentMoveToPosState::MoveAgentMoveToPosState(MoveAgent * move_agent) : MoveAgentState(move_agent, EMoveAgentState_MoveToPos)
{

}

GameLogic::MoveAgentMoveToPosState::~MoveAgentMoveToPosState()
{

}

void GameLogic::MoveAgentMoveToPosState::Enter(void * param)
{
	m_move_agent->SetVelocity(Vector3::zero);
	NavAgent *agent = m_move_agent->GetNavAgent();
	agent->SetPos(m_move_agent->GetPos());
	agent->TryMoveToPos(m_desired_pos);
	agent->Enable();
}

void GameLogic::MoveAgentMoveToPosState::Exit()
{
	m_move_agent->GetNavAgent()->StopMove();
}

void GameLogic::MoveAgentMoveToPosState::Update(long deltaMs)
{
	m_move_agent->GetNavAgent()->OnMoved();
}

void GameLogic::MoveAgentMoveToPosState::Flash(const Vector3 & val)
{
	m_move_agent->GetNavAgent()->SetPos(val);
}

void GameLogic::MoveAgentMoveToPosState::SetDesiredPos(const Vector3 &pos)
{
	m_desired_pos = pos;
}

