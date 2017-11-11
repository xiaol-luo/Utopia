#pragma once

#include "MoveAgentState.h"
#include "Common/Geometry/Vector3.h"

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
		virtual void Flash(const Vector3 &val);
		virtual bool IsDone();

		void SetDesiredPos(const Vector3 &pos);

	protected:
		Vector3 m_desired_pos;
	};
}

