#pragma once

#include "MoveObject.h"

namespace GameLogic
{
	class Player;
	class Scene;

	class Hero : public MoveObject
	{
	public:
		Hero();
		virtual ~Hero();

	public:
		void SetPlayer(Player *player) { m_Player = player; }
		Player * GetPlayer() { return m_Player; }
	private:
		Player *m_Player = nullptr;
	};
}
