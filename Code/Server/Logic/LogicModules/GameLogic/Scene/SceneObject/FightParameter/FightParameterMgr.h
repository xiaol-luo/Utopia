#pragma once

#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	class FightUnit;
	class FightParameter;

	class FightParameterMgr
	{
	public:
		FightParameterMgr(FightUnit *fight_unit);
		~FightParameterMgr();

		FightParameter *m_params[NetProto::EFP_COUNT];
		FightUnit *m_fight_unit;
	};
}