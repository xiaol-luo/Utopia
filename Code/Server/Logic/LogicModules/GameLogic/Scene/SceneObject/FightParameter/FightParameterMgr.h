#pragma once

#include "Network/Protobuf/BattleEnum.pb.h"
#include <queue>

namespace GameLogic
{
	class FightUnit;
	class FightParameter;

	class FightParameterMgr
	{
	public:
		FightParameterMgr(FightUnit *fight_unit);
		~FightParameterMgr();

		FightParameter * GetFightParam(NetProto::EFightParam efp);
		void AddBaseValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveBaseValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);

		void AddExtraPercent(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveExtraPercent(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);

		void AddExtraValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveExtraValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);

		void Recal(NetProto::EFightParam efp);
		int GetValue(NetProto::EFightParam efp, bool recal = false);

	protected:
		FightParameter *m_params[NetProto::EFP_COUNT];
		FightUnit *m_fight_unit;

	protected:
		void OnValueChange(NetProto::EFightParam efp, int new_value, int old_value);
		struct FightParamValueChangeEvent
		{
			FightParamValueChangeEvent(NetProto::EFightParam _efp, int _new_value, int _old_value)
			{
				efp = _efp;
				new_value = _new_value;
				old_value = _old_value;
			}
			NetProto::EFightParam efp;
			int new_value = 0;
			int old_value = 0;
		};
		std::queue<FightParamValueChangeEvent> m_fpvc_events;
		int m_fpvc_call_semaphore = 8;
	};
}