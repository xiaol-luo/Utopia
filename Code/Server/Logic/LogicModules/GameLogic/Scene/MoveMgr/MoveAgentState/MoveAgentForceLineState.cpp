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
	m_is_done = false;
	m_ticker.Restart(m_time_sec);
	m_start_pos = m_move_agent->GetPos();
	m_curr_pos = m_move_agent->GetPos();
	m_move_agent->SetVelocity(m_velocity);
}

void GameLogic::MoveAgentForceLineState::Exit()
{
	m_time_sec = 0;
	m_ignore_terrian = false;
	m_velocity = Vector3::zero;
	m_ticker.Restart(0);
}

void GameLogic::MoveAgentForceLineState::Update(long deltaMs)
{
	if (m_is_done)
		return;

	if (m_ignore_terrian)
	{
		if (m_ticker.InCd())
		{
			m_curr_pos = m_start_pos + m_velocity * m_ticker.ElaspeTime();
		}
		else
		{
			m_curr_pos = m_start_pos + m_velocity * m_ticker.GetCd();
			m_is_done = true;
		}
	}
	else
	{

	}

	m_move_agent->SetPos(m_curr_pos);
}

bool GameLogic::MoveAgentForceLineState::IsDone()
{
	return m_is_done;
}

void GameLogic::MoveAgentForceLineState::ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian)
{
	Vector2 velocity = dir;
	velocity.normalize();
	velocity = velocity * speed;
	m_velocity.x = velocity.x;
	m_velocity.y = 0;
	m_velocity.z = velocity.y;
	m_time_sec = time_sec;
	m_ignore_terrian = ignore_terrian;
}


