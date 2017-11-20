#pragma once

#include "FightParameter.h"
#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	class FightUnit;

	class FightParameterMgr
	{
	public:
		FightParameterMgr(FightUnit *fight_unit);
		~FightParameterMgr();

		FightParameter m_params[NetProto::EFP_COUNT];
		FightUnit *m_fight_unit;
	};
}