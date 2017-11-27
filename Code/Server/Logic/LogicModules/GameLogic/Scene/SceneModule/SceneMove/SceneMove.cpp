#include "SceneMove.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "recastnavigation/DetourCrowd/Include/DetourCrowd.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"

namespace GameLogic
{
	SceneMove::SceneMove() : SceneModule(MODULE_TYPE)
	{
	}

	SceneMove::~SceneMove()
	{
	}

	bool SceneMove::OnAwake()
	{
		m_nav_mesh = m_scene->GetModule<SceneNavMesh>()->GetNavMesh();
		this->GetSceneEvProxy()->Subscribe<SceneUnit *>(ESU_EnterScene,
			std::bind(&SceneMove::OnSceneUnitEnterScene, this, std::placeholders::_1));
		return true;
	}

	void SceneMove::OnUpdate()
	{
		long deltaMs = this->GetScene()->GetLogicDetalMs();
		m_nav_mesh->GetCrowd()->update(deltaMs * 0.001, nullptr);

		{
			std::vector<uint64_t> expired_ids;
			for (auto kv_pair : m_su_moves)
			{
				auto su_move = kv_pair.second.lock();
				if (nullptr == su_move)
				{
					expired_ids.push_back(kv_pair.first);
					continue;
				}
				su_move->UpdateState(deltaMs);
			}
			if (!expired_ids.empty())
			{
				for (uint64_t id : expired_ids)
					m_su_moves.erase(id);
			}
		}
	}

	void SceneMove::OnSceneUnitEnterScene(SceneUnit * su)
	{
		auto su_move = su->GetModule<SceneUnitMove>();
		if (nullptr != su_move)
			m_su_moves.insert_or_assign(su->GetId(), su_move);
	}
}


