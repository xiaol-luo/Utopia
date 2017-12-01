#pragma once

#include "Common/Geometry/Vector3.h"
#include "Network/Protobuf/BattleEnum.pb.h"

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
		virtual void Update(long deltaMs) = 0;
		virtual bool IsDone() { return false; }
		virtual void ForceDone() {}
		virtual void Flash(const Vector3 &val) {}
		NetProto::EMoveAgentState GetState() { return m_state; }

	protected:
		NetProto::EMoveAgentState m_state;
		SceneUnitMove *m_move_agent;
	};
}