#include "SceneUnitExample.h"

namespace GameLogic
{
	const ESceneUnitModule SceneUnitExample::MODULE_TYPE = ESceneUnitModule_Count;

	SceneUnitExample::SceneUnitExample() : SceneUnitModule(MODULE_TYPE)
	{

	}

	SceneUnitExample::~SceneUnitExample()
	{
	}
}