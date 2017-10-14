#pragma once

#include "MoveAgentState.h"

namespace GameLogic
{
	class MoveAgentIdleState : public MoveAgentState
	{
	public:
		MoveAgentIdleState(MoveAgent *move_agent);
		virtual ~MoveAgentIdleState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
	};
}
