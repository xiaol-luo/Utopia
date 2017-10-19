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
	m_last_elasped_time = 0;
	m_move_agent->SetVelocity(m_velocity);
	m_is_done = !m_ticker.InCd();
}

void GameLogic::MoveAgentForceLineState::Exit()
{
	m_time_sec = 0;
	m_ignore_terrian = false;
	m_velocity = Vector3::zero;
	m_ticker.Restart(0);
	m_last_elasped_time = 0;
}

void GameLogic::MoveAgentForceLineState::Update(long deltaMs)
{
	if (m_is_done)
		return;

	float time_span = 0;
	if (m_ticker.InCd())
	{
		time_span = m_ticker.ElaspeTime() - m_last_elasped_time;
		m_last_elasped_time = m_ticker.ElaspeTime();
	}
	else
	{
		time_span = m_ticker.GetCd() - m_last_elasped_time;
		m_last_elasped_time = m_ticker.GetCd();
		m_is_done = true;
	}

	Vector3 ret_pos = m_move_agent->GetPos();
	if (m_ignore_terrian)
	{
		ret_pos += m_velocity * time_span;
	}
	else
	{

	}

	m_move_agent->SetPos(ret_pos);
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


