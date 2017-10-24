#include "Hero.h"
#include "GameLogic/Player/Player.h"

namespace GameLogic
{
	Hero::Hero() : MoveObject(ESOT_Hero)
	{
	}

	Hero::~Hero()
	{

	}
	void Hero::SetPlayer(Player * player)
	{
		m_Player = player;
	}
}
