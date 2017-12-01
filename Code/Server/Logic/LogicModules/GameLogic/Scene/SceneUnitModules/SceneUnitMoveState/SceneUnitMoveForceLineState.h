#pragma once

#include "SceneUnitMoveState.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Utils/Ticker.h"

namespace GameLogic
{
	class SceneUnitMoveForceLineState : public SceneUnitMoveState
	{
	public:
		SceneUnitMoveForceLineState(SceneUnitMove *move_agent);
		virtual ~SceneUnitMoveForceLineState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(long deltaMs);
		virtual bool IsDone();
		virtual void ForceDone() { m_is_done = true; }
		virtual void Flash(const Vector3 &val);

		void ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian);

	protected:
		bool m_is_done = true;
		Vector3 m_velocity = Vector3::zero;
		float m_time_sec = 0;
		bool m_ignore_terrian = false;
		Ticker m_ticker;
		float m_last_elasped_time = 0;
		Vector3 m_hit_pos;
		Vector3 m_expected_pos;
	};
}
