#pragma once

#include <memory>

namespace GameLogic
{
	class SceneUnit;

	class EffectUtil
	{
	public:
		static bool UnitCanBeHurt(std::shared_ptr<SceneUnit> su);
		static bool UnitIsAlive(std::shared_ptr<SceneUnit> su);
	};
}

