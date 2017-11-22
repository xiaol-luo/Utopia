#pragma once

#include "MoveObject.h"
#include <queue>

namespace GameLogic
{
	class FightParameterMgr;

	class FightUnit : public MoveObject
	{
	public:
		FightUnit(ESceneObjectType obj_type);
		virtual ~FightUnit() override;
		virtual void OnEnterScene(Scene *scene) override;
		virtual void OnLeaveScene(Scene *scene) override;
		virtual void Update(long long now_ms) override;

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