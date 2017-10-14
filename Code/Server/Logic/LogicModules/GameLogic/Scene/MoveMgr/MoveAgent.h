#pragma once

#include <stdint.h>
#include "DetourCrowd.h"
#include "Common/Math/Vector3.h"
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
			std::function<void(MoveAgent *agent, EMoveAgentState old_state)> move_state_cb = nullptr;
			std::function<void(MoveAgent *agent, const Vector3 &old_pos)> post_change_cb = nullptr;
			std::function<void(MoveAgent *agent, const Vector3 &old_velocity)> velocity_change_cb = nullptr;
		};

	public:
		MoveAgent(MoveMgr *move_mgr);
		virtual ~MoveAgent();

	public:
		void SetId(uint64_t val) { m_id = val; }
		uint64_t GetId() { return m_id; }
		NavAgent * GetNavAgent() { return m_nav_agent; }

	protected:
		int64_t m_id = 0;
		MoveMgr *m_move_mgr = nullptr;
		NavAgent *m_nav_agent = nullptr;
		MoveAgentState *m_states[EMoveAgentState_Max];
		EMoveAgentState m_pre_state = EMoveAgentState_Idle;
		EMoveAgentState m_curr_state = EMoveAgentState_Idle;

	public:
		const Vector3 & GetPos() { return m_pos; }
		void SetPos(Vector3 val);
		const Vector3 & GetVelocity() { return m_velocity; }
		void SetVelocity(Vector3 val);
		float GetMoveMaxSpeed();
		void SetMoveMaxSpeed(float val);
		EventCallback & GetEventCb() { return m_event_cb; }
		void SetEventCb(const EventCallback &cb) { m_event_cb = cb; }

	protected:
		Vector3 m_pos;
		Vector3 m_velocity;
		EventCallback m_event_cb;
	};
}
