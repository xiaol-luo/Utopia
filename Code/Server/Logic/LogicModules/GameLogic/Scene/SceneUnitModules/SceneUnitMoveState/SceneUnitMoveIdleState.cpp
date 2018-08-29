#include "SceneUnitMoveIdleState.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"

GameLogic::SceneUnitMoveIdleState::SceneUnitMoveIdleState(SceneUnitMove * move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_Idle)
{

}

GameLogic::SceneUnitMoveIdleState::~SceneUnitMoveIdleState()
{

}

void GameLogic::SceneUnitMoveIdleState::Enter(void * param)
{
	m_move_agent->GetNavAgent()->StopMove();
	m_move_agent->GetNavAgent()->Enable();
	m_move_agent->SetVelocity(Vector3::zero);
}

void GameLogic::SceneUnitMoveIdleState::Exit()
{

}

void GameLogic::SceneUnitMoveIdleState::Update(int64_t deltaMs)
{

}

void GameLogic::SceneUnitMoveIdleState::CollectMoveDetail(NetProto::SceneUnitMove * msg)
{
}

