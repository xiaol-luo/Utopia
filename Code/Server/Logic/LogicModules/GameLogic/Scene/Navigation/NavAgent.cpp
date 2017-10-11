#include "NavAgent.h"
#include "NavMesh.h"

namespace GameLogic
{
	NavAgent::NavAgent(NavMesh *nav_mesh, uint64_t id) : m_nav_mesh(nav_mesh), m_id(id)
	{
		m_crowd = m_nav_mesh->GetCrowd();
		m_nav_mesh_query = m_nav_mesh->GetNavMeshQuery();
	}

	NavAgent::~NavAgent()
	{
		this->Disable();
	}

	void NavAgent::OnMoved()
	{
		if (!IsEnable())
			return;

		const dtCrowdAgent *dt_agent = m_crowd->getAgent(m_dt_agent_id);
		if (nullptr != dt_agent)
		{
			m_pos = Vector3(dt_agent->npos);
		}

		if (m_moved_cb)
			m_moved_cb(this);
	}

	void NavAgent::SetPos(Vector3 val)
	{
		m_pos = val;

		if (IsEnable())
		{
			auto agent = m_crowd->getEditableAgent(m_dt_agent_id);
			if (agent)
			{
				agent->npos[0] = m_pos.x;
				agent->npos[1] = m_pos.y;
				agent->npos[2] = m_pos.z;
			}
		}
	}

	void NavAgent::SetAgentParams(dtCrowdAgentParams val)
	{
		m_agent_params = val;

		if (IsEnable())
		{
			m_crowd->updateAgentParameters(m_dt_agent_id, &m_agent_params);
		}
	}
	void NavAgent::Enable()
	{
		if (IsEnable())
			return;

		float f_pos[3] = { m_pos.x, m_pos.y, m_pos.z };
		m_dt_agent_id = m_crowd->addAgent(f_pos, &m_agent_params);
	}

	void NavAgent::Disable()
	{
		if (!IsEnable())
			return;

		m_crowd->removeAgent(m_dt_agent_id);
		m_dt_agent_id = DT_AGENT_INVALID_ID;
	}
}


