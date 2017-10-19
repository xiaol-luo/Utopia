#pragma once

#include "MoveAgentState.h"

namespace GameLogic
{
	class MoveAgentFlashState : public MoveAgentState
	{
	public:
		MoveAgentFlashState(MoveAgent *move_agent);
		virtual ~MoveAgentFlashState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
	};
}
