#pragma once

#include <queue>
#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	class FightParameterMgr;
	class Scene;

	class FightUnit 
	{
	public:
		FightUnit(int obj_type);
		virtual ~FightUnit();
		virtual void OnEnterScene(Scene *scene);
		virtual void OnLeaveScene(Scene *scene);
		virtual void Update(long long now_ms);

	public:
		inline FightParameterMgr * GetFightParamMgr() { return m_fight_param_mgr; }
		void OnFightParamValueChange(NetProto::EFightParam efp, int new_value, int old_value);
		bool IsAlive();
	protected:
		FightParameterMgr *m_fight_param_mgr = nullptr;
		int m_hp = 0;
		int m_mp = 0;
		void OnMaxHpChange(int new_value, int old_value);
	};
}