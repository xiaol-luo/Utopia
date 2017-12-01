#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace GameLogic
{
	class SceneUnitSkills : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Skills;
	public:
		SceneUnitSkills();
		virtual ~SceneUnitSkills() override;
	};
}
