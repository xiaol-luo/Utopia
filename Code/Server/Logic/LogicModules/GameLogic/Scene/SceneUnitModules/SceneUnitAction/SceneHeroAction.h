#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace GameLogic
{
	class SceneHeroAction : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Action;
	public:
		SceneHeroAction();
		virtual ~SceneHeroAction() override;
	};
}

