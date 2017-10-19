#pragma once

#include "MoveAgentState.h"

namespace GameLogic
{
	class MoveAgentMoveToDirState : public MoveAgentState
	{
	public:
		MoveAgentMoveToDirState(MoveAgent *move_agent);
		virtual ~MoveAgentMoveToDirState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
		virtual void Flash(const Vector3 &val);
		void SetDesiredDir(float dir);

	protected:
		float m_desired_dir = 0.0f;
	};
}
