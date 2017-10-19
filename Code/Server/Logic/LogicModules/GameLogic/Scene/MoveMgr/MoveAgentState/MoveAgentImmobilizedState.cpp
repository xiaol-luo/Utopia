#include "MoveAgentImmobilizedState.h"
#include "Common/Math/Vector3.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Utils/TimerUtil.h"


GameLogic::MoveAgenImmobilizedState::MoveAgenImmobilizedState(MoveAgent * move_agent) : MoveAgentState(move_agent, EMoveAgentState_Immobilized)
{

}

GameLogic::MoveAgenImmobilizedState::~MoveAgenImmobilizedState()
{

}

void GameLogic::MoveAgenImmobilizedState::Enter(void * param)
{
	m_is_done = false;
	m_move_agent->SetVelocity(Vector3::zero);
	m_ticker.RestartWithEndTimestamp(m_end_timestamp_ms * 0.001);
	m_is_done = !m_ticker.InCd();
}

void GameLogic::MoveAgenImmobilizedState::Exit()
{
	m_end_timestamp_ms = 0;
	m_is_done = true;
	m_ticker.Restart(0);
}

void GameLogic::MoveAgenImmobilizedState::Update(long deltaMs)
{
	if (m_is_done)
		return;

	m_is_done = !m_ticker.InCd();
}

bool GameLogic::MoveAgenImmobilizedState::IsDone()
{
	return m_is_done;
}

void GameLogic::MoveAgenImmobilizedState::ImmobilizeEndMs(long end_ms)
{
	m_end_timestamp_ms = end_ms;
}



