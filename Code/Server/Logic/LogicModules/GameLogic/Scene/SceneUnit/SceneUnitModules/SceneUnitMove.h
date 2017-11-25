#pragma once

#include <unordered_map>
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace GameLogic
{
	class SceneUnitMove : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Move;
	public: 
		SceneUnitMove();
		virtual ~SceneUnitMove() override;
	};
}
