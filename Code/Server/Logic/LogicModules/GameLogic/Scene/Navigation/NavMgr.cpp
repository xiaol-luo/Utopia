#include "NavMgr.h"
#include "NavMesh.h"
#include "DetourCrowd.h"
#include "DetourNavMeshQuery.h"
#include <assert.h>
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Timer/ITimerModule.h"

namespace GameLogic
{

	GameLogic::NavMgr::NavMgr()
	{
		
	}

	GameLogic::NavMgr::~NavMgr()
	{
		m_dtCrowd = nullptr;
		m_dtNavMeshQuery = nullptr;
	}

	bool NavMgr::Init(NavMesh *navMesh)
	{
		if (nullptr == navMesh)
			return false;
		m_dtCrowd = navMesh->GetCrowd();
		m_dtNavMeshQuery = navMesh->GetNavMeshQuery();
		return m_dtCrowd && m_dtNavMeshQuery;
	}

	void GameLogic::NavMgr::Update()
	{
		long deltaMs = GlobalServerLogic->GetTimerModule()->DeltaMs();
		m_dtCrowd->update(deltaMs * 0.001, nullptr);
	}
}
