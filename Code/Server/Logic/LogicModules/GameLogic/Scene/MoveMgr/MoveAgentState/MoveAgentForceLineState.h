#pragma once

#include "MoveAgentState.h"
#include "Common/Math/Vector2.h"

namespace GameLogic
{
	class MoveAgentForceLineState : public MoveAgentState
	{
	public:
		MoveAgentForceLineState(MoveAgent *move_agent);
		virtual ~MoveAgentForceLineState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
		virtual bool IsDone();

		void ForceMoveLine(Vector2 dir, float speed, float time_sec, bool ignore_terrian);

	protected:
		bool m_is_done = true;
		Vector2 m_dir = 0;
		float m_speed = 0;
		float m_time_sec = 0;
		bool m_ignore_terrian = false;
	};
}
