#include "NavAgent.h"
#include "NavMesh.h"
#include <cfloat>
#include "Common/Geometry/GeometryUtils.h"
#include "Common/Geometry/Vector2.h"

namespace GameLogic
{
	NavAgent::NavAgent(NavMesh *nav_mesh) : m_nav_mesh(nav_mesh)
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
		if (nullptr != dt_agent && DT_CROWDAGENT_STATE_INVALID != dt_agent->state)
		{
			if (DT_CROWDAGENT_TARGET_VALID != dt_agent->targetState || DT_CROWDAGENT_TARGET_VELOCITY != dt_agent->targetState)
			{
				m_pos = Vector3(dt_agent->npos);
				m_velocity = Vector3(dt_agent->vel);
			}
			if (m_moved_cb)
				m_moved_cb(this);
		}
	}

	void NavAgent::SetPos(Vector3 val)
	{
		Vector3 fit_pos;
		dtPolyRef poly_ref;
		m_nav_mesh->FindNearestPoint(val, &poly_ref, fit_pos);
		m_pos = fit_pos;

		if (IsEnable())
		{
			this->Disable();
			this->Enable();
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
		m_move_type = EMoveType_MovePos;
		m_desired_move_pos = pos;
		TryResumeMove();
	}

	void NavAgent::TryMoveToDir(float angle)
	{
		this->StopMove();
		m_move_type = EMoveType_MoveDir;
		m_desired_move_dir = angle;
		TryResumeMove();
	}

	void NavAgent::StopMove()
	{
		m_move_type = EMoveType_None;
		m_desired_move_dir = 0.0f;
		m_desired_move_pos = Vector3::zero;
		m_velocity = Vector3::zero;
		if (IsEnable())
		{
			m_crowd->resetMoveTarget(m_dt_agent_id);
		}
	}

	void NavAgent::TryResumeMove()
	{
		if (!IsEnable())
			return;

		if (EMoveType_MoveDir == m_move_type)
		{
			// m_crowd->requestMoveVelocity()
			if (abs(m_desired_move_dir) >= FLT_EPSILON)
			{
				Vector2 dir = GeometryUtils::RotateVector2(Vector2::up, m_desired_move_dir);
				Vector3 velocity = Vector3(dir.x, 0, dir.y) * this->GetMaxSpeed();
				m_crowd->requestMoveVelocity(m_dt_agent_id, velocity.toPointer());
			}
		}
		if (EMoveType_MovePos == m_move_type)
		{
			Vector3 target_pos;
			dtPolyRef poly_ref;
			m_nav_mesh->FindNearestPoint(m_desired_move_pos, &poly_ref, target_pos);
			m_crowd->requestMoveTarget(m_dt_agent_id, poly_ref, target_pos.toPointer());
		}
	}
}


