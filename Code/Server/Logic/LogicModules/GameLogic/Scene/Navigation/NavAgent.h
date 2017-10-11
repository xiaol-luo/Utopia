#include <stdint.h>
#include "DetourCrowd.h"
#include "Common/Math/Vector3.h"
#include <functional>

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
		Vector3 GetPos() { return m_pos; }
		void SetPos(Vector3 val);
		dtCrowdAgentParams GetAgentParams() { return m_agent_params; }
		void SetAgentParams(dtCrowdAgentParams val);
		void Enable();
		void Disable();
		bool IsEnable() { return DT_AGENT_INVALID_ID != m_dt_agent_id; }
		uint64_t GetId() { return m_id; }

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
	};
}
