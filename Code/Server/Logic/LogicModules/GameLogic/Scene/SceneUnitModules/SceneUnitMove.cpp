#include "SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveForceLineState.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveForcePosState.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveIdleState.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveImmobilizedState.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveToPosState.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveToDirState.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "Common/Macro/AllMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"
#include "GameLogic/Scene/Defines/ESceneEvent.h"
#include <cstdlib>
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "ServerLogics/ServerLogic.h"

namespace GameLogic
{
	const ESceneUnitModule SceneUnitMove::MODULE_TYPE = ESceneUnitModule_Move;

	bool NeedImmobilized(SceneUnitMove *sum)
	{
		// 如果被定身或者眩晕了，就进入不动的状态
		std::shared_ptr<SceneUnitFightParam> sufp = sum->GetModule<SceneUnitFightParam>();
		if (nullptr == sufp)
			return false;
		if (sufp->IsStateActive(NetProto::EFP_Immobilized) || sufp->IsStateActive(NetProto::EFP_Dizzy))
			return true;
		return false;
	}

	SceneUnitMove::SceneUnitMove() : SceneUnitModule(MODULE_TYPE)
	{

	}

	SceneUnitMove::~SceneUnitMove()
	{
		if (nullptr != m_nav_agent)
		{
			m_nav_agent->Disable();
			delete m_nav_agent; m_nav_agent = nullptr;
		}
	}

	void SceneUnitMove::UpdateState(int64_t deltaMs)
	{
		if (nullptr == m_curr_state)
			return;

		m_curr_state->Update(deltaMs);
		if (m_curr_state->IsDone())
		{
			SceneUnitMoveState *next_state = m_next_state;
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			this->EnterState(next_state->GetState());

			// 如果被定身或者眩晕了，就进入不动的状态
			if (NeedImmobilized(this))
				this->Immobilized();
		}
	}

	void SceneUnitMove::OnEnterScene()
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
		this->AwakeNavAgent();

		this->GetSceneEvProxy()->Subscribe(ES_TestHeartBeat, std::bind(&SceneUnitMove::TestAction, this));

		m_test_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, m_owner->GetScene()));
		m_test_ticker.SetCd(5);
	}
	void SceneUnitMove::OnDestroy()
	{
		m_next_state = nullptr;
		m_curr_state = nullptr;
		for (auto state : m_states)
			delete state;
		memset(m_states, 0, sizeof(m_states));
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
		if (val == m_velocity)
			return;

		Vector3 old_val = m_velocity;
		m_velocity = val;
		this->GetEvProxy()->Fire<Vector3, Vector3>(ESU_VolecityChange, m_velocity, old_val);
	}
	std::vector<SyncClientMsg> SceneUnitMove::CollectPBInit()
	{
		return std::move(this->CollectPbMutable());
	}
	std::vector<SyncClientMsg> SceneUnitMove::CollectPbMutable()
	{
		std::vector<SyncClientMsg> msgs;
		{
			NetProto::SceneUnitMove *msg = m_owner->GetScene()->CreateProtobuf<NetProto::SceneUnitMove>();
			msg->set_su_id(this->GetId());
			msg->set_move_agent_state(m_curr_state->GetState());
			msgs.push_back(SyncClientMsg(NetProto::PID_SceneUnitMove, msg));
		}
		return std::move(msgs);
	}
	void SceneUnitMove::EnterState(NetProto::EMoveAgentState new_state, void * param)
	{
		NetProto::EMoveAgentState old_state = m_curr_state->GetState();
		m_curr_state->Exit();
		m_curr_state = m_states[new_state];
		m_curr_state->Enter(param);
		this->SetPbDirty();
		this->GetEvProxy()->Fire<NetProto::EMoveAgentState, NetProto::EMoveAgentState>(
			ESU_MoveStateChange, new_state, old_state);
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
		m_nav_mesh->FindNearestPoint(pos, &poly_ref, fix_pos);
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
			this->GetNavAgent()->StopMove();
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
			this->EnterState(NetProto::EMoveAgentState_Idle);
		}
		if (NetProto::EMoveState_Move == CalMoveState(m_next_state->GetState()))
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
		}
	}

	void SceneUnitMove::CancelForceMove()
	{
		if (NetProto::EMoveState_ForceMove == CalMoveState(this->GetMoveAgentState()))
		{
			m_curr_state->ForceDone();
		}
		if (NetProto::EMoveState_ForceMove == CalMoveState(m_next_state->GetState()))
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
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

	void SceneUnitMove::Immobilized()
	{
		if (NetProto::EMoveState_Immobilized == this->GetMoveState())
			return;

		SceneUnitMoveImmobilizedState *state = dynamic_cast<SceneUnitMoveImmobilizedState *>(m_states[NetProto::EMoveAgentState_Immobilized]);
		state->ImmobilizeEndMs(m_owner->GetScene()->GetLogicMs() + INT_MAX);
		if (NetProto::EMoveState_ForceMove == this->GetMoveState())
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Immobilized];
		}
		else
		{
			m_next_state = m_curr_state; // MOVE OR IDLE
			this->EnterState(NetProto::EMoveAgentState_Immobilized);
		}
	}

	void SceneUnitMove::CancelImmobilized()
	{
		if (NetProto::EMoveState_Immobilized == this->GetMoveState())
		{
			m_curr_state->ForceDone();
		}
		if (NetProto::EMoveState_Immobilized == CalMoveState(m_next_state->GetState()))
		{
			m_next_state = m_states[NetProto::EMoveAgentState_Idle];
		}
	}

	void SceneUnitMove::Flash(const Vector3 & val)
	{
		Vector3 fix_pos; dtPolyRef poly_ref;
		if (!m_nav_mesh->FindNearestPoint(val, &poly_ref, fix_pos))
		{
			Vector3 now_pos = this->GetPos();
			if (!m_nav_mesh->Raycast(now_pos, val, fix_pos))
				fix_pos = now_pos;
		}
		for (int i = 0; i < NetProto::EMoveAgentState_Max; ++i)
			m_states[i]->Flash(fix_pos);
		this->SetPos(fix_pos);
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT, 
			"Flash [{}]:{:3.2f}, {:3.2f}, {:3.2f}",
			this->GetMoveAgentState(), fix_pos.x, fix_pos.y, fix_pos.z);
	}

	void SceneUnitMove::OnImmobilizeStateChange(bool attach)
	{
		if (NeedImmobilized(this))
			this->Immobilized();
		else
			this->CancelImmobilized();
	}

	void SceneUnitMove::OnInit()
	{
		this->GetEvProxy()->Subscribe<bool>(ESU_ImmobilizedChange, std::bind(&SceneUnitMove::OnImmobilizeStateChange, this, std::placeholders::_1));
		this->GetEvProxy()->Subscribe<bool>(ESU_DizzinessChange, std::bind(&SceneUnitMove::OnImmobilizeStateChange, this, std::placeholders::_1));
	}

	void SceneUnitMove::TestAction()
	{
		if (!m_test_ticker.InCd())
		{
			if (m_owner->GetPlayerId() <= 0)
			{
				m_test_ticker.Restart();
				this->TryMoveToPos(Vector3(std::rand() % 100, 0, std::rand() % 100));
			}
		}
	}
}
