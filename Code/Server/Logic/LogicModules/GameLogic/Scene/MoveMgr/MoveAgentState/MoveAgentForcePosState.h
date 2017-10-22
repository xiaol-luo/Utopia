#pragma once

#include "MoveAgentState.h"

namespace GameLogic
{
	class MoveAgentForcePosState : public MoveAgentState
	{
	public:
		MoveAgentForcePosState(MoveAgent *move_agent);
		virtual ~MoveAgentForcePosState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
		virtual bool IsDone() { return m_is_done; }
		virtual void ForceDone() { m_is_done = true; }

		void ForcePos(const Vector3 &destination, float speed);
		void ForcePos(const Vector3 &destination);

	private:
		Vector3 m_destination;
		float m_speed = 0;
		bool m_is_done = true;
		const Vector3 CalNextVolecity();
	};
}
