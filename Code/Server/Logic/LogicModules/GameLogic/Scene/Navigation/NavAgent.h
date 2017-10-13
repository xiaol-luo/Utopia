#pragma once

#include <stdint.h>
#include "DetourCrowd.h"
#include "Common/Math/Vector3.h"
#include <functional>
#include "GameLogic/Scene/Defines/SceneObjectDefine.h"

namespace GameLogic
{
	class NavAgent;
	class NavMesh;
	using MovedCallback = void(*)(NavAgent *agent);

	class NavAgent
	{
	public:
		const static uint64_t INVALID_ID = 0;
	public:
		NavAgent(NavMesh *nav_mesh, uint64_t id);
		virtual ~NavAgent();

		void SetMovedCb(std::function<void(NavAgent *)> cb) { m_moved_cb = cb; }
		void OnMoved();

	public:
		const Vector3 & GetPos() { return m_pos; }
		void SetPos(Vector3 val);
		const dtCrowdAgentParams & GetAgentParams() { return m_agent_params; }
		void SetAgentParams(dtCrowdAgentParams val);
		void Enable();
		void Disable();
		bool IsEnable() { return DT_AGENT_INVALID_ID != m_dt_agent_id; }
		uint64_t GetId() { return m_id; }
		const Vector3 & GetVelocity() { return m_velocity; }
		const float GetMaxSpeed() { return m_agent_params.maxSpeed; }
		void SetMaxSpeed(float val);

	private:
		uint64_t m_id = INVALID_ID;
		NavMesh *m_nav_mesh = nullptr;
		dtCrowd *m_crowd = nullptr;
		dtNavMeshQuery *m_nav_mesh_query = nullptr;
		std::function<void(NavAgent *)> m_moved_cb = nullptr;

		static const int DT_AGENT_INVALID_ID = -1;
		int m_dt_agent_id = DT_AGENT_INVALID_ID;
		dtCrowdAgentParams m_agent_params;
		Vector3 m_pos;
		Vector3 m_velocity;

	public:
		void TryMoveToPos(const Vector3 &pos);
		void TryMoveToDir(float angle);
		void StopMove();
		void TryResumeMove();

		EMoveType m_move_type = EMoveType_None;
		Vector3 m_desired_move_pos;
		float m_desired_move_dir = 0;
	};
}
