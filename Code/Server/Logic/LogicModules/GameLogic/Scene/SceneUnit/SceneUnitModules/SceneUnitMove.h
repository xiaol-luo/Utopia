#pragma once

#include <unordered_map>
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	class NavMesh;
	class NavAgent;
	class SceneUnitTransform;
	class SceneUnitMoveState;

	class SceneUnitMove : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Move;
	public: 
		SceneUnitMove();
		virtual ~SceneUnitMove() override;
		void UpdateState();

	protected:
		virtual void OnAwake() override;
		virtual void OnDestroy() override;

	public:
		void SetPos(const Vector3 &pos);
		Vector3 GetPos();
		const Vector3 & GetVelocity() { return m_velocity; }
		void SetVelocity(const Vector3 &val);
	protected:
		Vector3 m_velocity;

	public:
		NavAgent * GetNavAgent() { return m_nav_agent; }
		NavMesh * GetNavMesh() { return m_nav_mesh; }
	protected:
		NavMesh *m_nav_mesh = nullptr;
		NavAgent *m_nav_agent = nullptr;
		SceneUnitMoveState *m_states[NetProto::EMoveAgentState_Max];
		SceneUnitMoveState *m_next_state = nullptr;
		SceneUnitMoveState *m_curr_state = nullptr;
		void EnterState(NetProto::EMoveAgentState newState, void *param = nullptr);
		void AwakeNavAgent();
		void DestroyNavAgent();

	public:
		static NetProto::EMoveState CalMoveState(NetProto::EMoveAgentState state);
		NetProto::EMoveAgentState GetMoveAgentState();
		NetProto::EMoveState GetMoveState();
		bool IsLoseControl();

	};
}
