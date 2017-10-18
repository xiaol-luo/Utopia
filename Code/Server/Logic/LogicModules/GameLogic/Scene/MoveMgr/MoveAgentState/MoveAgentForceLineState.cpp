#include "MoveAgentForceLineState.h"
#include "Common/Math/Vector3.h"
#include "Common/Math/Vector2.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

GameLogic::MoveAgentForceLineState::MoveAgentForceLineState(MoveAgent * move_agent) : MoveAgentState(move_agent, EMoveAgentState_ForceLine)
{
}

GameLogic::MoveAgentForceLineState::~MoveAgentForceLineState()
{
}

void GameLogic::MoveAgentForceLineState::Enter(void * param)
{
	m_move_agent->SetVelocity(Vector3::zero);
}

void GameLogic::MoveAgentForceLineState::Exit()
{
	m_is_done = true;
	m_speed = 0;
	m_time_sec = 0;
	m_ignore_terrian = false;
}

void GameLogic::MoveAgentForceLineState::Update(long deltaMs)
{
}

bool GameLogic::MoveAgentForceLineState::IsDone()
{
	return m_is_done;
}

void GameLogic::MoveAgentForceLineState::ForceMoveLine(Vector2 dir, float speed, float time_sec, bool ignore_terrian)
{
	m_dir = dir;
	m_dir.normalize();
	m_speed = speed;
	m_time_sec = time_sec;
	m_ignore_terrian = ignore_terrian;
}


