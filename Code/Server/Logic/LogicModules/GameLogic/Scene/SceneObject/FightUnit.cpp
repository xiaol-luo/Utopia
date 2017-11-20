#include "FightUnit.h"
#include "FightParameter/FightParameterMgr.h"

namespace GameLogic
{
	FightUnit::FightUnit(ESceneObjectType obj_type) : MoveObject(obj_type)
	{
		m_fight_param_mgr = new FightParameterMgr(this);
	}

	FightUnit::~FightUnit()
	{
		delete m_fight_param_mgr;
	}
}