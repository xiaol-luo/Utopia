#pragma once

#include "SceneUnitMoveState.h"

namespace GameLogic
{
	class SceneUnitMoveIdleState : public SceneUnitMoveState
	{
	public:
		SceneUnitMoveIdleState(SceneUnitMove *move_agent);
		virtual ~SceneUnitMoveIdleState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
	};
}
