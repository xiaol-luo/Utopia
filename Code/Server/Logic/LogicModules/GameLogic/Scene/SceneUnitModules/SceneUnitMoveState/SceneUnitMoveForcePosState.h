#pragma once

#include "SceneUnitMoveState.h"

namespace GameLogic
{
	class SceneUnitMoveForcePosState : public SceneUnitMoveState
	{
	public:
		SceneUnitMoveForcePosState(SceneUnitMove *move_agent);
		virtual ~SceneUnitMoveForcePosState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(int64_t deltaMs);
		virtual bool IsDone() { return m_is_done; }
		virtual void ForceDone() { m_is_done = true; }

		void ForcePos(const Vector3 &destination, float speed);
		void ForcePos(const Vector3 &destination);

		virtual void CollectMoveDetail(NetProto::SceneUnitMove *msg);

	private:
		Vector3 m_destination;
		float m_speed = 0;
		bool m_is_done = true;
		const Vector3 CalNextVolecity();
	};
}
