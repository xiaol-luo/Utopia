#include "MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentIdleState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentMoveToPosState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentMoveToDirState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentForceLineState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentImmobilizedState.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentForcePosState.h"
#include "Common/Utils/TimerUtil.h"
#include "Common/Utils/LogUtil.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"

GameLogic::EMoveState GameLogic::MoveAgent::CalMoveState(GameLogic::EMoveAgentState state)
{
	EMoveState ret = EMoveState_Idle;
	switch (state)
	{
	case EMoveAgentState_Idle:
		ret = EMoveState_Idle;
		break;
	case EMoveAgentState_MoveToDir:
	case EMoveAgentState_MoveToPos:
		ret = EMoveState_Move;
		break;
	case EMoveAgentState_ForceLine:
	// case EMoveAgentState_ForceSky:
		ret = EMoveState_ForceMove;
		break;
	case EMoveAgentState_Immobilized:
		ret = EMoveState_Immobilized;
		break;
	}

	return ret;
}

GameLogic::MoveAgent::MoveAgent(MoveMgr * move_mgr) : m_move_mgr(move_mgr)
{
	m_nav_agent = new NavAgent(move_mgr->GetNavMesh());
	m_nav_agent->SetMovedCb(std::bind(&GameLogic::MoveAgent::OnNavAgentMoved, this, std::placeholders::_1));

	m_states[EMoveAgentState_Idle] = new MoveAgentIdleState(this);
	m_states[EMoveAgentState_MoveToDir] = new MoveAgentMoveToDirState(this);
	m_states[EMoveAgentState_MoveToPos] = new MoveAgentMoveToPosState(this);
	m_states[EMoveAgentState_Immobilized] = new MoveAgenImmobilizedState(this);
	m_states[EMoveAgentState_ForceLine] = new MoveAgentForceLineState(this);
	m_states[EMoveAgentState_ForcePos] = new MoveAgentForcePosState(this);
	m_next_state = m_states[EMoveState_Idle];
	m_curr_state = m_states[EMoveState_Idle];
}

GameLogic::MoveAgent::~MoveAgent()
{
	for (int i = 0; i < EMoveAgentState_Max; ++i)
	{
		delete m_states[i]; m_states[i] = nullptr;
	}
}

void GameLogic::MoveAgent::EnterState(EMoveAgentState new_state, void *param)
{
	EMoveAgentState old_state = m_curr_state->GetState();
	m_curr_state->Exit();
	m_curr_state = m_states[new_state];
	m_curr_state->Enter(param);
	if (nullptr != m_event_cb.move_state_cb)
		m_event_cb.move_state_cb(this, old_state);
}

GameLogic::EMoveAgentState GameLogic::MoveAgent::GetMoveAgentState()
{
	return m_curr_state->GetState();
}

GameLogic::EMoveState GameLogic::MoveAgent::GetMoveState()
{
	return CalMoveState(this->GetMoveAgentState());
}

bool GameLogic::MoveAgent::LoseControl()
{
	return this->GetMoveState() > EMoveState_Move;
}

void GameLogic::MoveAgent::NavDisable()
{
	this->GetNavAgent()->Disable();
}

void GameLogic::MoveAgent::NavEnable()
{
	this->GetNavAgent()->Enable();
}

bool GameLogic::MoveAgent::IsNavEnable()
{
	return this->GetNavAgent()->IsEnable();
}

void GameLogic::MoveAgent::NavSetPos(const Vector3 & val)
{
	this->GetNavAgent()->SetPos(val);
}

void GameLogic::MoveAgent::SetPos(const Vector3 &pos)
{
	Vector3 old_pos = m_pos;
	m_pos = pos;
	// LogUtil::Debug(LogModule::LOGGER_ID_STDOUT + 2, "SetPos [{}]:{:3.2f}, {:3.2f}, {:3.2f}", 
	//	this->GetMoveAgentState(), pos.x, pos.y, pos.z);
	if (m_event_cb.post_change_cb)
		m_event_cb.post_change_cb(this, old_pos);
}

void GameLogic::MoveAgent::SetVelocity(const Vector3 &val)
{
	Vector3 old_velocity = m_velocity;
	m_velocity = val;
	if (nullptr != m_event_cb.velocity_change_cb)
		m_event_cb.velocity_change_cb(this, val);
}

float GameLogic::MoveAgent::GetNavMaxSpeed()
{
	return m_nav_agent->GetMaxSpeed();
}

void GameLogic::MoveAgent::SetNavMaxSpeed(float val)
{
	m_nav_agent->SetMaxSpeed(val);
}

void GameLogic::MoveAgent::Flash(const Vector3 & val)
{
	Vector3 fix_pos; dtPolyRef poly_ref;
	if (!m_move_mgr->GetNavMesh()->FindNearestPoint(val, poly_ref, fix_pos))
	{
		if (!m_move_mgr->GetNavMesh()->Raycast(m_pos, val, fix_pos))
			fix_pos = m_pos;
	}

	for (int i = 0; i < EMoveAgentState_Max; ++i)
	{
		m_states[i]->Flash(fix_pos);
	}
	this->SetPos(fix_pos);
	LogUtil::Debug(LogModule::LOGGER_ID_STDOUT + 2, "Flash [{}]:{:3.2f}, {:3.2f}, {:3.2f}",
		this->GetMoveAgentState(), fix_pos.x, fix_pos.y, fix_pos.z);
}

void GameLogic::MoveAgent::OnNavAgentMoved(NavAgent * agent)
{
	this->SetPos(agent->GetPos());
	this->SetVelocity(agent->GetVelocity());
}

void GameLogic::MoveAgent::Update(long deltaMs)
{
	m_curr_state->Update(deltaMs);
	if (m_curr_state->IsDone())
	{
		MoveAgentState *next_state = m_next_state;
		m_next_state = m_states[EMoveAgentState_Idle];
		this->EnterState(next_state->GetState());
	}
}

void GameLogic::MoveAgent::TryMoveToPos(const Vector3 &pos)
{
	MoveAgentMoveToPosState *state = dynamic_cast<MoveAgentMoveToPosState *>(m_states[EMoveAgentState_MoveToPos]);
	state->SetDesiredPos(pos);
	if (!LoseControl())
	{
		m_next_state = m_states[EMoveAgentState_Idle];
		this->EnterState(state->GetState());
	}
	else
	{
		m_next_state = state;
	}
}

void GameLogic::MoveAgent::TryMoveToDir(float angle)
{
	MoveAgentMoveToDirState *state = dynamic_cast<MoveAgentMoveToDirState *>(m_states[EMoveAgentState_MoveToDir]);
	state->SetDesiredDir(angle);
	if (!LoseControl())
	{
		m_next_state = m_states[EMoveAgentState_Idle];
		this->EnterState(state->GetState());
	}
	else
	{
		m_next_state = state;
	}
}

void GameLogic::MoveAgent::CancelMove()
{
	if (EMoveState_Move == this->GetMoveState())
	{
		m_next_state = m_states[EMoveAgentState_Idle];
		this->EnterState(EMoveAgentState_Idle);
	}
	else
	{
		this->GetNavAgent()->StopMove();
		if (EMoveState_Move == CalMoveState(m_next_state->GetState()))
			m_next_state = m_states[EMoveAgentState_Idle];
	}
}

void GameLogic::MoveAgent::CancelForceMove()
{
	if (EMoveState_ForceMove == this->GetMoveAgentState())
	{
		m_curr_state->ForceDone();
	}
	else
	{
		if (EMoveState_ForceMove == CalMoveState(m_next_state->GetState()))
		{
			m_next_state->ForceDone();
			m_next_state = m_states[EMoveAgentState_Idle];
		}
	}
}

void GameLogic::MoveAgent::ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian)
{
	MoveAgentForceLineState *state = dynamic_cast<MoveAgentForceLineState *>(m_states[EMoveAgentState_ForceLine]);
	state->ForceMoveLine(dir, speed, time_sec, ignore_terrian);
	if (EMoveState_ForceMove != this->GetMoveState())
		m_next_state = m_curr_state;
	this->EnterState(EMoveAgentState_ForceLine);
}

void GameLogic::MoveAgent::ForcePos(const Vector3 & destination, float speed)
{
	MoveAgentForcePosState *state = dynamic_cast<MoveAgentForcePosState *>(m_states[EMoveAgentState_ForcePos]);
	state->ForcePos(destination, speed);
	if (EMoveState_ForceMove != this->GetMoveState())
		m_next_state = m_curr_state;
	this->EnterState(EMoveAgentState_ForcePos);
}

void GameLogic::MoveAgent::ChangeForcePosDestination(const Vector3 & destination)
{
	MoveAgentForcePosState *state = dynamic_cast<MoveAgentForcePosState *>(m_states[EMoveAgentState_ForcePos]);
	state->ForcePos(destination);
}

void GameLogic::MoveAgent::Immobilized(long ms)
{
	MoveAgenImmobilizedState *state = dynamic_cast<MoveAgenImmobilizedState *>(m_states[EMoveAgentState_Immobilized]);
	state->ImmobilizeEndMs(TimerUtil::NowMs() + ms);
	if (EMoveState_ForceMove == this->GetMoveState())
	{
		m_next_state = m_states[EMoveAgentState_Immobilized];
	}
	else 
	{
		if (EMoveState_Immobilized != this->GetMoveState()) 
			m_next_state = m_curr_state; // MOVE OR IDLE
		this->EnterState(EMoveAgentState_Immobilized);
	}
}

void GameLogic::MoveAgent::CancelImmobilized()
{
	if (EMoveState_Immobilized == this->GetMoveAgentState())
	{
		m_curr_state->ForceDone();
	}
	else
	{
		if (EMoveState_Immobilized == CalMoveState(m_next_state->GetState()))
		{
			m_next_state->ForceDone();
			m_next_state = m_states[EMoveAgentState_Idle];
		}
	}
}






