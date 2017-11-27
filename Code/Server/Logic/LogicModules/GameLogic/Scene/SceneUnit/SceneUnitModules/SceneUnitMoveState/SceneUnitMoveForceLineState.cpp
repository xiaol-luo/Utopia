#include "SceneUnitMoveForceLineState.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMove.h"

GameLogic::SceneUnitMoveForceLineState::SceneUnitMoveForceLineState(SceneUnitMove * move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_ForceLine)
{
}

GameLogic::SceneUnitMoveForceLineState::~SceneUnitMoveForceLineState()
{
}

void GameLogic::SceneUnitMoveForceLineState::Enter(void * param)
{
	m_is_done = false;
	m_ticker.Restart(m_time_sec);
	m_last_elasped_time = 0;
	m_is_done = !m_ticker.InCd();
	m_move_agent->GetNavAgent()->Disable();
	m_move_agent->SetVelocity(m_velocity);
	if (!m_ignore_terrian)
	{
		m_expected_pos = m_move_agent->GetPos() + m_velocity * m_ticker.LeftTime();
		m_move_agent->GetNavMesh()->Raycast(m_move_agent->GetPos(), m_expected_pos, m_hit_pos);
	}
}

void GameLogic::SceneUnitMoveForceLineState::Exit()
{
	m_is_done = true;
}

void GameLogic::SceneUnitMoveForceLineState::Update(long deltaMs)
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
	if (abs(time_span) < FLT_MIN)
		return;
	Vector3 move_distance = m_velocity * time_span;
	move_distance.y = 0;
	Vector3 ret_pos = m_move_agent->GetPos() + move_distance;
	if (m_ignore_terrian)
	{
		m_move_agent->SetPos(ret_pos);
	}
	else
	{
		Vector3 now_distance = m_hit_pos - m_move_agent->GetPos();
		if (now_distance.sqrMagnitude() > FLT_MIN)
		{
			Vector3 nor1 = now_distance;
			Vector3 nor2 = ret_pos - m_hit_pos; // 获得从m_hit_pos指向ret_pos的向量
			nor1.y = 0; nor2.y = 0;
			nor1.normalize(); nor2.normalize();
			if (Vector3::dot(nor1, nor2) > 0) // 夹角小于90度，也即ret_pos越过了m_hit_pos
			{
				ret_pos = m_hit_pos;
			}
			m_move_agent->SetPos(ret_pos);
		}
	}
}

bool GameLogic::SceneUnitMoveForceLineState::IsDone()
{
	return m_is_done;
}

void GameLogic::SceneUnitMoveForceLineState::Flash(const Vector3 &val)
{
	if (!m_ignore_terrian)
	{
		Vector3 end_pos = val + m_velocity * m_ticker.LeftTime();
		m_move_agent->GetNavMesh()->Raycast(val, end_pos, m_hit_pos);
		if (m_move_agent->GetVelocity().sqrMagnitude() < FLT_MIN)
			m_move_agent->SetVelocity(m_velocity);
	}
}

void GameLogic::SceneUnitMoveForceLineState::ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian)
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


