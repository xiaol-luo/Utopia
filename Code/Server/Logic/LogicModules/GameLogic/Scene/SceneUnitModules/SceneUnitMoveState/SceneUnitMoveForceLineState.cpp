#include "SceneUnitMoveForceLineState.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include <functional>
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

GameLogic::SceneUnitMoveForceLineState::SceneUnitMoveForceLineState(SceneUnitMove * move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_ForceLine)
{
	m_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, m_move_agent->GetOwner()->GetScene()));
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

void GameLogic::SceneUnitMoveForceLineState::Update(int64_t deltaMs)
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
		if (now_distance.SqrMagnitude() > FLT_MIN)
		{
			Vector3 nor1 = now_distance;
			Vector3 nor2 = ret_pos - m_hit_pos; // ��ô�m_hit_posָ��ret_pos������
			nor1.y = 0; nor2.y = 0;
			nor1.Normalize(); nor2.Normalize();
			if (Vector3::Dot(nor1, nor2) > 0) // �н�С��90�ȣ�Ҳ��ret_posԽ����m_hit_pos
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
		if (m_move_agent->GetVelocity().SqrMagnitude() < FLT_MIN)
			m_move_agent->SetVelocity(m_velocity);
	}
}

void GameLogic::SceneUnitMoveForceLineState::ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian)
{
	Vector2 velocity = dir;
	velocity.Normalize();
	velocity = velocity * speed;
	m_velocity.x = velocity.x;
	m_velocity.y = 0;
	m_velocity.z = velocity.y;
	m_time_sec = time_sec;
	m_ignore_terrian = ignore_terrian;
}

void GameLogic::SceneUnitMoveForceLineState::CollectMoveDetail(NetProto::SceneUnitMove * msg)
{
	::NetProto::PBVector2* v = msg->mutable_force_line_velocity();
	v->set_x(m_velocity.x);
	v->set_y(m_velocity.z);
	msg->set_force_line_elasped_sec(m_last_elasped_time);
	msg->set_force_line_total_sec(m_time_sec);
	::NetProto::PBVector2* p = msg->mutable_force_line_end_pos();
	p->set_x(m_hit_pos.x);
	p->set_y(m_hit_pos.z);
}


