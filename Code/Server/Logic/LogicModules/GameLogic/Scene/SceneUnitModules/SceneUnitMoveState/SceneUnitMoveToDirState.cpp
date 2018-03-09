#include "SceneUnitMoveToDirState.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"

GameLogic::SceneUnitMoveToDirState::SceneUnitMoveToDirState(SceneUnitMove * move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_MoveToDir)
{

}

GameLogic::SceneUnitMoveToDirState::~SceneUnitMoveToDirState()
{

}

void GameLogic::SceneUnitMoveToDirState::Enter(void * param)
{
	m_move_agent->SetVelocity(Vector3::zero);
	NavAgent *agent = m_move_agent->GetNavAgent();
	agent->SetPos(m_move_agent->GetPos());
	agent->TryMoveToDir(m_desired_dir);
	agent->Enable();
}

void GameLogic::SceneUnitMoveToDirState::Exit()
{
	m_move_agent->GetNavAgent()->StopMove();
}

void GameLogic::SceneUnitMoveToDirState::Update(int64_t deltaMs)
{
	m_move_agent->GetNavAgent()->OnMoved();
}

void GameLogic::SceneUnitMoveToDirState::Flash(const Vector3 & val)
{
	m_move_agent->GetNavAgent()->SetPos(val);
}

void GameLogic::SceneUnitMoveToDirState::SetDesiredDir(float dir)
{
	m_desired_dir = dir;
}


