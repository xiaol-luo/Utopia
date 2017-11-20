#pragma once

#include "MoveObject.h"

namespace GameLogic
{
	class FightParameterMgr;

	class FightUnit : public MoveObject
	{
	public:
		FightUnit(ESceneObjectType obj_type);
		virtual ~FightUnit() override;

	protected:
		FightParameterMgr *m_fight_param_mgr = nullptr;
	};
}