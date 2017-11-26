#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"

namespace GameLogic
{
	class SceneMove : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE = ESceneModule_Move;
	public:
		SceneMove();
		virtual ~SceneMove() override;
	};
}
