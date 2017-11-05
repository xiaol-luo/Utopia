#include "MoveAgentMoveToPosState.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Math/Vector3.h"
#include "Common/Math/Vector2.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"

GameLogic::MoveAgentMoveToPosState::MoveAgentMoveToPosState(MoveAgent * move_agent) : MoveAgentState(move_agent, NetProto::EMoveAgentState_MoveToPos)
{

}

GameLogic::MoveAgentMoveToPosState::~MoveAgentMoveToPosState()
{

}

void GameLogic::MoveAgentMoveToPosState::Enter(void * param)
{
	Vector3 from = m_move_agent->GetPos();
	GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT, 
		"MoveAgentMoveToPosState::Enter: from{:3.2f}, {:3.2f}, {:3.2f} to {:3.2f}, {:3.2f}, {:3.2f} #",
		from.x, from.y, from.z,
		m_desired_pos.x, m_desired_pos.y, m_desired_pos.z);
	m_move_agent->SetVelocity(Vector3::zero);
	m_move_agent->SetPos(m_move_agent->GetPos());
	NavAgent *agent = m_move_agent->GetNavAgent();
	agent->SetPos(m_move_agent->GetPos());
	agent->TryMoveToPos(m_desired_pos);
	m_move_agent->NavEnable();
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

bool GameLogic::MoveAgentMoveToPosState::IsDone()
{
	bool ret = (m_desired_pos.xz() - m_move_agent->GetPos().xz()).sqrMagnitude() < MOVE_TO_POS_IGNORE_SQR_DISTANCE;
	return ret;
}

void GameLogic::MoveAgentMoveToPosState::SetDesiredPos(const Vector3 &pos)
{
	m_desired_pos = pos;
}

