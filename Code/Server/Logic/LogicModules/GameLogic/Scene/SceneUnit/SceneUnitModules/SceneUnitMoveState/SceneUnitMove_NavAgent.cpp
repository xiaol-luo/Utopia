#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"


namespace GameLogic
{
	void SceneUnitMove::AwakeNavAgent()
	{


		this->EnterState(NetProto::EMoveAgentState_Idle);
	}

	void SceneUnitMove::DestroyNavAgent()
	{
		m_nav_agent->Disable();
	}
}
