#pragma once

#include "SceneUnitMoveState.h"
#include "Common/Geometry/Vector3.h"

namespace GameLogic
{
	class SceneUnitMoveToPosState : public SceneUnitMoveState
	{
	public: 
		SceneUnitMoveToPosState(SceneUnitMove *move_agent);
		virtual ~SceneUnitMoveToPosState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(int64_t deltaMs);
		virtual void Flash(const Vector3 &val);
		virtual bool IsDone();

		void SetDesiredPos(const Vector3 &pos);

	protected:
		Vector3 m_desired_pos;
	};
}

