#include "SceneNavMesh.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/GameLogicModule.h"
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"

namespace GameLogic
{
	SceneNavMesh::SceneNavMesh() : SceneModule(MODULE_TYPE)
	{
		m_nav_mesh = new GameLogic::NavMesh();
	}

	SceneNavMesh::~SceneNavMesh()
	{
	}
	bool SceneNavMesh::OnAwake()
	{
		bool ret;
		Config::CsvSceneConfig *scene_cfg = m_scene->GetCfg()->scene_cfg;
		ret = m_nav_mesh->LoadTerrain(m_scene->GetGameLogic()->GetCfgRootPath() + "/" + scene_cfg->terrain_file_path);
		assert(ret);
		return ret;
	}
}


