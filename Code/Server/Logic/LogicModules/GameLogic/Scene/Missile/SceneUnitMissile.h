#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace GameLogic
{
	class SceneUnitMissile : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Missle;
	public:
		SceneUnitMissile();
		virtual ~SceneUnitMissile() override;
	};
}