#pragma once

#include "MoveAgentState.h"

namespace GameLogic
{
	class MoveAgentMoveToPosState : public MoveAgentState
	{
	public: 
		MoveAgentMoveToPosState(MoveAgent *move_agent);
		virtual ~MoveAgentMoveToPosState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
	};
}

