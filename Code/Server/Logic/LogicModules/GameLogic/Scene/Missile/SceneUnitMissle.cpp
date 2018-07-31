#include "SceneUnitMissile.h"

namespace GameLogic
{
	const ESceneUnitModule SceneUnitMissile::MODULE_TYPE = ESceneUnitModule_Missle;

	SceneUnitMissile::SceneUnitMissile() : SceneUnitModule(MODULE_TYPE)
	{

	}

	SceneUnitMissile::~SceneUnitMissile()
	{
	}
}

