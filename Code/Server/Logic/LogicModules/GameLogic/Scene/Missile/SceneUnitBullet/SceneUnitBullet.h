#pragma once

#include "GameLogic/Scene/Missile/SceneUnitMissile.h"

namespace GameLogic
{
	class SceneUnitBullet : public SceneUnitMissile
	{
	public:
		SceneUnitBullet();
		virtual ~SceneUnitBullet() override;
	};
}