#pragma once

#include <stdint.h>
#include "DetourCrowd.h"
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/Vector3.h"
#include <functional>
#include "GameLogic/Scene/Defines/SceneObjectDefine.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentState.h"

namespace GameLogic
{
	class MoveMgr;
	class NavAgent;

	class MoveAgent
	{
	public:
		const static uint64_t INVALID_ID = 0;
		struct EventCallback
		{
			std::function<void(MoveAgent *agent, NetProto::EMoveAgentState old_state)> move_state_cb = nullptr;
			std::function<void(MoveAgent *agent, const Vector3 &old_pos)> post_change_cb = nullptr;
			std::function<void(MoveAgent *agent, const Vector3 &old_velocity)> velocity_change_cb = nullptr;
		};
		
		static NetProto::EMoveState CalMoveState(NetProto::EMoveAgentState state);
	public:
		MoveAgent(MoveMgr *move_mgr);
		virtual ~MoveAgent();

	public:
		void SetId(uint64_t val) { m_id = val; }
		uint64_t GetId() { return m_id; }
		NavAgent * GetNavAgent() { return m_nav_agent; }
		MoveMgr * GetMoveMgr() { return m_move_mgr; }

	protected:
		int64_t m_id = 0;
		MoveMgr *m_move_mgr = nullptr;
		NavAgent *m_nav_agent = nullptr;
		MoveAgentState *m_states[NetProto::EMoveAgentState_Max];
		MoveAgentState *m_next_state = nullptr;
		MoveAgentState *m_curr_state = nullptr;

		void EnterState(NetProto::EMoveAgentState newState, void *param=nullptr);

	public:
		NetProto::EMoveAgentState GetMoveAgentState();
		NetProto::EMoveState GetMoveState();
		bool LoseControl();
		void NavDisable();
		void NavEnable();
		bool IsNavEnable();
		void NavSetPos(const Vector3 &val);
		float GetNavMaxSpeed();
		void SetNavMaxSpeed(float val);
		const Vector3 & GetPos() { return m_pos; }
		void SetPos(const Vector3 &val);
		const Vector3 & GetVelocity() { return m_velocity; }
		void SetVelocity(const Vector3 &val);
		EventCallback & GetEventCb() { return m_event_cb; }
		void SetEventCb(const EventCallback &cb) { m_event_cb = cb; }

	protected:
		Vector3 m_pos;
		Vector3 m_velocity;
		EventCallback m_event_cb;
		void OnNavAgentMoved(NavAgent *agent);

	public:
		void Update(long deltaMs);
		void TryMoveToPos(const Vector3 &pos);
		void TryMoveToDir(float angle);
		void CancelMove();
		void CancelForceMove();
		void ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian);
		void ForcePos(const Vector3 &destination, float speed);
		void ChangeForcePosDestination(const Vector3 &destination);
		void Immobilized(long ms);
		void CancelImmobilized();
		void Flash(const Vector3 &val);
	};
}
