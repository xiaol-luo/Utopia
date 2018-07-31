#include "SceneNavMesh.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/GameLogicModule.h"
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"

namespace GameLogic
{
	const ESceneModule SceneNavMesh::MODULE_TYPE = ESceneModule_NavMesh;

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
		std::string terrainPath = m_scene->GetGameLogic()->GetCfgRootPath() + scene_cfg->terrain_file_path;
		ret = m_nav_mesh->LoadTerrain(terrainPath);
		assert(ret);
		return ret;
	}
}


