#pragma once

#include "Common/Geometry/Vector3.h"
#include "Network/Protobuf/BattleEnum.pb.h"
#include "Network/Protobuf/Battle.pb.h"
#include <float.h>

namespace GameLogic
{
	class SceneUnitMove;

	class SceneUnitMoveState
	{
	public:
		SceneUnitMoveState(SceneUnitMove *move_agent, NetProto::EMoveAgentState state) : m_state(state), m_move_agent(move_agent) {}
		virtual ~SceneUnitMoveState() {}

		virtual void Enter(void *param) = 0;
		virtual void Exit() = 0;
		virtual void Update(int64_t deltaMs) = 0;
		virtual bool IsDone() { return false; }
		virtual void ForceDone() {}
		virtual void Flash(const Vector3 &val) {}
		NetProto::EMoveAgentState GetState() { return m_state; }

		virtual void CollectMoveDetail(NetProto::SceneUnitMove *msg) = 0;

	protected:
		NetProto::EMoveAgentState m_state;
		SceneUnitMove *m_move_agent;
	};
}