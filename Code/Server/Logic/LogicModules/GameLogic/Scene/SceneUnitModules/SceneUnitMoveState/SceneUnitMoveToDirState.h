#pragma once

#include "SceneUnitMoveState.h"

namespace GameLogic
{
	class SceneUnitMoveToDirState : public SceneUnitMoveState
	{
	public:
		SceneUnitMoveToDirState(SceneUnitMove *move_agent);
		virtual ~SceneUnitMoveToDirState();

		virtual void Enter(void *param);
		virtual void Exit();
		virtual void Update(int64_t deltaMs);
		virtual void Flash(const Vector3 &val);
		void SetDesiredDir(float dir);

		virtual void CollectMoveDetail(NetProto::SceneUnitMove *msg);

	protected:
		float m_desired_dir = 0.0f;
	};
}
