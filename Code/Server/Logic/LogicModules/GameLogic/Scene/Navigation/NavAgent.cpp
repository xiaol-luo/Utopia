#include "NavAgent.h"
#include "NavMesh.h"
#include <cfloat>
#include "Common/Math/MathUtils.h"

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
			m_velocity = Vector3(dt_agent->vel);
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

	void NavAgent::SetMaxSpeed(float val)
	{
		m_agent_params.maxSpeed = val;
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
		this->TryResumeMove();
	}

	void NavAgent::Disable()
	{
		if (!IsEnable())
			return;

		m_crowd->removeAgent(m_dt_agent_id);
		m_dt_agent_id = DT_AGENT_INVALID_ID;
	}

	void NavAgent::TryMoveToPos(const Vector3 &pos)
	{
		this->StopMove();
		m_move_type = MoveType_Pos;
		m_desired_move_pos = pos;
		TryResumeMove();
	}

	void NavAgent::TryMoveToDir(float angle)
	{
		this->StopMove();
		m_move_type = MoveType_Dir;
		m_desired_move_dir = angle;
		TryResumeMove();
	}

	void NavAgent::StopMove()
	{
		m_move_type = MoveType_None;
		m_desired_move_dir = 0.0f;
		m_desired_move_pos = Vector3::zero;
		if (IsEnable())
		{
			m_crowd->resetMoveTarget(m_dt_agent_id);
		}
	}

	void NavAgent::TryResumeMove()
	{
		if (!IsEnable())
			return;

		if (MoveType_Dir == m_move_type)
		{
			// m_crowd->requestMoveVelocity()
			if (abs(m_desired_move_dir) >= FLT_EPSILON)
			{
				Vector3 dir = MathUtils::Angle2Vector(m_desired_move_dir);
				Vector3 velocity = dir * this->GetMaxSpeed();
				m_crowd->requestMoveVelocity(m_dt_agent_id, velocity.toPointer());
			}
		}
		if (MoveType_Pos == m_move_type)
		{
			Vector3 target_pos;
			dtPolyRef poly_ref;
			m_nav_mesh->FindNearestPoint(m_desired_move_pos, 0, &poly_ref, &target_pos);
			m_crowd->requestMoveTarget(m_dt_agent_id, poly_ref, target_pos.toPointer());
		}
	}
}


