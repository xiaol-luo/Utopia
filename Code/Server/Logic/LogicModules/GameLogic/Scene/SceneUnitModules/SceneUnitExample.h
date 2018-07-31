#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace GameLogic
{
	class SceneUnitExample : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE/* = ESceneUnitModule_Count*/;
	public:
		SceneUnitExample();
		virtual ~SceneUnitExample() override;
	};
}