#pragma once

#include "FightUnit.h"

namespace GameLogic
{
	class Player;
	class Scene;

	class Hero : public FightUnit
	{
	public:
		Hero();
		virtual ~Hero();

	public:
		void SetPlayer(Player *player);
		Player * GetPlayer() { return m_Player; }
	private:
		Player *m_Player = nullptr;
	};
}
