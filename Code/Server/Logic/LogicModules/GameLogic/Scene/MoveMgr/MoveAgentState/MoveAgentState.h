#pragma once

namespace GameLogic
{
	class MoveAgent;

	enum  EMoveAgentState
	{
		EMoveAgentState_Idle = 0,
		EMoveAgentState_MoveToPos,
		EMoveAgentState_MoveToDir,
		EMoveAgentState_ForceLine,
		EMoveAgentState_ForceSky,

		EMoveAgentState_Max,
	};

	class MoveAgentState
	{
	public:
		MoveAgentState(MoveAgent *move_agent, EMoveAgentState state) : m_state(state), m_move_agent(move_agent) {}
		virtual ~MoveAgentState() {}

		virtual void Enter(void *param) = 0;
		virtual void Exit() = 0;
		virtual void Update(long deltaMs) = 0;

	protected:
		EMoveAgentState m_state;
		MoveAgent *m_move_agent;
	};
}