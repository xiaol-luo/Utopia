#pragma once

#include "MoveAgentState.h"

namespace GameLogic
{
	class MoveAgenImmobilizedState : public MoveAgentState
	{
	public:
		MoveAgenImmobilizedState(MoveAgent *move_agent);
		virtual ~MoveAgenImmobilizedState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
	};
}
