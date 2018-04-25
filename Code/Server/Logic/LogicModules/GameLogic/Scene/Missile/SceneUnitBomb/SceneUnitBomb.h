#pragma once

#include "GameLogic/Scene/Missile/SceneUnitMissile.h"

namespace GameLogic
{
	class SceneUnitBomb : public SceneUnitMissile
	{
	public:
		SceneUnitBomb();
		virtual ~SceneUnitBomb() override;
	};
}