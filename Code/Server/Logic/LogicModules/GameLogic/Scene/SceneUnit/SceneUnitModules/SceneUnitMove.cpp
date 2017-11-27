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

	void SceneUnitMove::UpdateState()
	{

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
}