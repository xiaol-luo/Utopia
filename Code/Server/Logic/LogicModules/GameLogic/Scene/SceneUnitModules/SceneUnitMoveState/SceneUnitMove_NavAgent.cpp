#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"


namespace GameLogic
{
	void SceneUnitMove::AwakeNavAgent()
	{
		m_nav_agent = new NavAgent(m_nav_mesh);
		dtCrowdAgentParams params;
		{
			memset(&params, 0, sizeof(params));
			params.radius = 2.0f;
			params.height = 2.0f;
			params.maxAcceleration = 32 * 40;
			params.maxSpeed = 6.0f;
			params.collisionQueryRange = params.radius * 12.0f;
			params.pathOptimizationRange = params.radius * 30.0f;
			params.separationWeight = 0.1f;
			params.updateFlags = 0;
			params.updateFlags |= DT_CROWD_ANTICIPATE_TURNS;
			params.updateFlags |= DT_CROWD_OPTIMIZE_VIS;
			params.updateFlags |= DT_CROWD_OPTIMIZE_TOPO;
			params.updateFlags |= DT_CROWD_OBSTACLE_AVOIDANCE;
			if (params.separationWeight > 0.001f) params.updateFlags |= DT_CROWD_SEPARATION;
			params.obstacleAvoidanceType = 3;
			// params.avoidancePriority = 0.5f; 
			params.queryFilterType = 0;
		}
		m_nav_agent->SetPos(this->GetPos());
		m_nav_agent->SetAgentParams(params);
		m_nav_agent->SetMovedCb(std::bind(&SceneUnitMove::OnNavAgentMoved, this, std::placeholders::_1));
		m_nav_agent->Enable();

		this->EnterState(NetProto::EMoveAgentState_Idle);
	}

	void SceneUnitMove::DestroyNavAgent()
	{
		m_nav_agent->SetMovedCb(nullptr);
		m_nav_agent->Disable();
		delete m_nav_agent; m_nav_agent = nullptr;
	}

	void SceneUnitMove::OnNavAgentMoved(NavAgent *agent)
	{
		this->SetPos(agent->GetPos());
		this->SetVelocity(agent->GetVelocity());
	}
}
