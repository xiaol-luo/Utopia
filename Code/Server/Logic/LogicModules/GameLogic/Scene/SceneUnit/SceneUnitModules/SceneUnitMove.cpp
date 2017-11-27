#include "SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveForceLineState.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveForcePosState.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveIdleState.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveImmobilizedState.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveToPosState.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveToDirState.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"

namespace GameLogic
{
	SceneUnitMove::SceneUnitMove() : SceneUnitModule(MODULE_TYPE)
	{
		m_states[NetProto::EMoveAgentState_Idle] = new SceneUnitMoveIdleState(this);
		m_states[NetProto::EMoveAgentState_MoveToDir] = new SceneUnitMoveToDirState(this);
		m_states[NetProto::EMoveAgentState_MoveToPos] = new SceneUnitMoveToPosState(this);
		m_states[NetProto::EMoveAgentState_Immobilized] = new SceneUnitMoveImmobilizedState(this);
		m_states[NetProto::EMoveAgentState_ForceLine] = new SceneUnitMoveForceLineState(this);
		m_states[NetProto::EMoveAgentState_ForcePos] = new SceneUnitMoveForcePosState(this);
		m_next_state = m_states[NetProto::EMoveState_Idle];
		m_curr_state = m_states[NetProto::EMoveState_Idle];

		SceneNavMesh *scene_navmesh = m_owner->GetScene()->GetModule<SceneNavMesh>();
		m_nav_mesh = scene_navmesh->GetNavMesh();
		m_nav_agent = new NavAgent(m_nav_mesh);
	}

	SceneUnitMove::~SceneUnitMove()
	{
		m_nav_agent->Disable();
		delete m_nav_agent; m_nav_agent = nullptr;
	}

	void SceneUnitMove::UpdateState(long deltaMs)
	{
		m_curr_state->Update(deltaMs);
		if (m_curr_state->IsDone())
		{
			SceneUnitMoveState *next_state = m_next_state;
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			this->EnterState(next_state->GetState());
		}
	}

	void SceneUnitMove::OnAwake()
	{
		this->AwakeNavAgent();
	}
	void SceneUnitMove::OnDestroy()
	{
		this->DestroyNavAgent();
	}

	void SceneUnitMove::SetPos(const Vector3 & pos)
	{
		m_owner->GetTransform()->SetLocalPos(pos);
	}

	Vector3 SceneUnitMove::GetPos()
	{
		return m_owner->GetTransform()->GetPos();
	}

	void SceneUnitMove::SetVelocity(const Vector3 & val)
	{
		m_velocity = val;
		// TODO : CB
	}
	void SceneUnitMove::EnterState(NetProto::EMoveAgentState new_state, void * param)
	{
		m_curr_state->Exit();
		m_curr_state = m_states[new_state];
		m_curr_state->Enter(param);
		// TODO : CB
	}

	NetProto::EMoveState SceneUnitMove::CalMoveState(NetProto::EMoveAgentState state)
	{
		NetProto::EMoveState ret = NetProto::EMoveState_Idle;
		switch (state)
		{
		case NetProto::EMoveAgentState_Idle:
			ret = NetProto::EMoveState_Idle;
			break;
		case NetProto::EMoveAgentState_MoveToDir:
		case NetProto::EMoveAgentState_MoveToPos:
			ret = NetProto::EMoveState_Move;
			break;
		case NetProto::EMoveAgentState_ForceLine:
		case NetProto::EMoveAgentState_ForcePos:
			ret = NetProto::EMoveState_ForceMove;
			break;
		case NetProto::EMoveAgentState_Immobilized:
			ret = NetProto::EMoveState_Immobilized;
			break;
		}

		return ret;
	}

	NetProto::EMoveAgentState SceneUnitMove::GetMoveAgentState()
	{
		return m_curr_state->GetState();
	}

	NetProto::EMoveState SceneUnitMove::GetMoveState()
	{
		return CalMoveState(this->GetMoveAgentState());
	}

	bool SceneUnitMove::IsLoseControl()
	{
		return this->GetMoveState() > NetProto::EMoveState_Move;
	}


	void SceneUnitMove::TryMoveToPos(const Vector3 &pos)
	{
		SceneUnitMoveToPosState *state = dynamic_cast<SceneUnitMoveToPosState *>(m_states[NetProto::EMoveAgentState_MoveToPos]);
		dtPolyRef poly_ref = 0; Vector3 fix_pos = pos;
		m_nav_mesh->FindNearestPoint(pos, poly_ref, fix_pos);
		state->SetDesiredPos(fix_pos);
		if (!IsLoseControl())
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			this->EnterState(state->GetState());
		}
		else
		{
			m_next_state = state;
		}
	}

	void SceneUnitMove::TryMoveToDir(float angle)
	{
		SceneUnitMoveToDirState *state = dynamic_cast<SceneUnitMoveToDirState *>(m_states[NetProto::EMoveAgentState_MoveToDir]);
		state->SetDesiredDir(angle);
		if (!IsLoseControl())
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			this->EnterState(state->GetState());
		}
		else
		{
			m_next_state = state;
		}
	}

	void SceneUnitMove::CancelMove()
	{
		if (NetProto::EMoveState_Move == this->GetMoveState())
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			this->EnterState(NetProto::EMoveAgentState_Idle);
		}
		else
		{
			this->GetNavAgent()->StopMove();
			if (NetProto::EMoveState_Move == CalMoveState(m_next_state->GetState()))
				m_next_state = m_states[NetProto::EMoveAgentState_Idle];
		}
	}

	void SceneUnitMove::CancelForceMove()
	{
		if (NetProto::EMoveState_ForceMove == this->GetMoveAgentState())
		{
			m_curr_state->ForceDone();
		}
		else
		{
			if (NetProto::EMoveState_ForceMove == CalMoveState(m_next_state->GetState()))
			{
				m_next_state->ForceDone();
				m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			}
		}
	}

	void SceneUnitMove::ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian)
	{
		SceneUnitMoveForceLineState *state = dynamic_cast<SceneUnitMoveForceLineState *>(m_states[NetProto::EMoveAgentState_ForceLine]);
		state->ForceMoveLine(dir, speed, time_sec, ignore_terrian);
		if (NetProto::EMoveState_ForceMove != this->GetMoveState())
			m_next_state = m_curr_state;
		this->EnterState(NetProto::EMoveAgentState_ForceLine);
	}

	void SceneUnitMove::ForcePos(const Vector3 & destination, float speed)
	{
		SceneUnitMoveForcePosState *state = dynamic_cast<SceneUnitMoveForcePosState *>(m_states[NetProto::EMoveAgentState_ForcePos]);
		state->ForcePos(destination, speed);
		if (NetProto::EMoveState_ForceMove != this->GetMoveState())
			m_next_state = m_curr_state;
		this->EnterState(NetProto::EMoveAgentState_ForcePos);
	}

	void SceneUnitMove::ChangeForcePosDestination(const Vector3 & destination)
	{
		SceneUnitMoveForcePosState *state = dynamic_cast<SceneUnitMoveForcePosState *>(m_states[NetProto::EMoveAgentState_ForcePos]);
		state->ForcePos(destination);
	}

	void SceneUnitMove::Immobilized(long ms)
	{
		SceneUnitMoveImmobilizedState *state = dynamic_cast<SceneUnitMoveImmobilizedState *>(m_states[NetProto::EMoveAgentState_Immobilized]);
		state->ImmobilizeEndMs(m_owner->GetScene()->GetLogicMs() + ms);
		if (NetProto::EMoveState_ForceMove == this->GetMoveState())
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Immobilized];
		}
		else
		{
			if (NetProto::EMoveState_Immobilized != this->GetMoveState())
				m_next_state = m_curr_state; // MOVE OR IDLE
			this->EnterState(NetProto::EMoveAgentState_Immobilized);
		}
	}

	void SceneUnitMove::CancelImmobilized()
	{
		if (NetProto::EMoveState_Immobilized == this->GetMoveAgentState())
		{
			m_curr_state->ForceDone();
		}
		else
		{
			if (NetProto::EMoveState_Immobilized == CalMoveState(m_next_state->GetState()))
			{
				m_next_state->ForceDone();
				m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			}
		}
	}

}