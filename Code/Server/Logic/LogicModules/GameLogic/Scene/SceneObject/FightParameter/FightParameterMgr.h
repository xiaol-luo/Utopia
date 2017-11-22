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

	protected:
		void OnValueChange(NetProto::EFightParam efp, int new_value, int old_value);
		FightParameter *m_params[NetProto::EFP_COUNT];
		FightUnit *m_fight_unit;
	};
}