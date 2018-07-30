#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "FightParam.h"
#include <queue>
#include <tuple>
#include <vector>

namespace GameLogic
{
	class EffectBase;

	class SceneUnitFightParam : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_FightParam;
	public:
		SceneUnitFightParam();
		virtual ~SceneUnitFightParam() override;

	public:
		FightParam * GetParam(NetProto::EFightParam efp);
		FightParam * GetParamFix(NetProto::EFightParam efp);

		void AddBaseValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveBaseValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void AddBaseValueFix(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveBaseValueFix(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);

		void AddExtraPercent(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveExtraPercent(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void AddExtraPercentFix(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveExtraPercentFix(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);

		void AddExtraValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveExtraValue(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void AddExtraValueFix(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);
		void RemoveExtraValueFix(NetProto::EFightParam efp, int val, bool recal = true, int unique_id = 0);

		void Recal(NetProto::EFightParam efp, bool include_fix);
		int GetValue(NetProto::EFightParam efp, bool include_fix=true);
		void RecalFix(NetProto::EFightParam efp);
		int GetValueFix(NetProto::EFightParam efp, bool recal = false);

	public:
		void AttachState(NetProto::EFightParam efp);
		void DeattachState(NetProto::EFightParam efp);
		bool IsStateActive(NetProto::EFightParam efp);
		bool IsDead() { return this->IsStateActive(NetProto::EFP_Dead); }
		bool IsBlind() { return this->IsStateActive(NetProto::EFP_Blind); }
		bool IsDizzy() { return this->IsStateActive(NetProto::EFP_Dizzy); }
		bool IsSilence() { return this->IsStateActive(NetProto::EFP_Silence); }

	protected:
		FightParam *m_params[NetProto::EFP_COUNT];
		FightParam *m_fix_params[NetProto::EFP_COUNT];
		void OnValueChange(bool is_fix, NetProto::EFightParam efp, int new_value, int old_value);
		void FireEventHelp(bool is_fix, NetProto::EFightParam efp, int new_value, int old_value);
		bool m_ev_firing = false;
		std::queue<std::tuple<bool, NetProto::EFightParam, int, int>> m_ev_queue;
	protected:
		void OnInit() override;
		void OnDestroy() override;
		void ForTestInitParam();
		void ForTestInitFixParam();

		bool HasParam(NetProto::EFightParam efp);
		bool HasFixParam(NetProto::EFightParam efp);
		bool IsState(NetProto::EFightParam efp);
		void CheckStateChange(bool is_fix, NetProto::EFightParam efp, int new_value, int old_value);

	public:
		int GetHp();
		int AddHp(int delta, EffectBase *effect);
		int GetMp();
		int AddMp(int delta, EffectBase *effect);
		
	protected:
		int m_hp = INT_MAX / 2;
		int m_mp = INT_MAX / 2;
	};
}