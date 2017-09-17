#pragma once

#include "MoveObject.h"

namespace GameLogic
{
	class Scene;

	class Npc : public MoveObject
	{
	public:
		Npc();
		virtual ~Npc();
	};
}