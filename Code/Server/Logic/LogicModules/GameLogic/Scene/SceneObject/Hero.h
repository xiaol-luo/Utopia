#pragma once

#include "MoveObject.h"

namespace GameLogic
{
	class Player;

	class Hero : public MoveObject
	{
	public:
		Hero(Player *player);
		virtual ~Hero();

	private:
		Player *m_Player = nullptr;
	};
}
