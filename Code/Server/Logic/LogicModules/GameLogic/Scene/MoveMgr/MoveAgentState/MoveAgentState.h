#pragma once

#include "GameLogic/Scene/Defines/SceneObjectDefine.h"
#include "Common/Math/Vector3.h"
#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	class MoveAgent;

	class MoveAgentState
	{
	public:
		MoveAgentState(MoveAgent *move_agent, NetProto::EMoveAgentState state) : m_state(state), m_move_agent(move_agent) {}
		virtual ~MoveAgentState() {}

		virtual void Enter(void *param) = 0;
		virtual void Exit() = 0;
		virtual void Update(long deltaMs) = 0;
		virtual bool IsDone() { return false; }
		virtual void ForceDone() {}
		virtual void Flash(const Vector3 &val) {}

	public:
		NetProto::EMoveAgentState GetState() { return m_state; }

	protected:
		NetProto::EMoveAgentState m_state;
		MoveAgent *m_move_agent;
	};
}