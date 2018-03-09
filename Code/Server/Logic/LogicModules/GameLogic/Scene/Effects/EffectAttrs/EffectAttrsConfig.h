#pragma once

#include "GameLogic/Scene/Effects/EffectConfigBase.h"
#include "GameLogic/Scene/SceneUnitModules/FightParam.h"

namespace Config
{
	struct CsvEffectAttrsConfig;
}

namespace GameLogic
{
	class SceneEffects;
	class SceneUnitFightParam;

	enum FightParamAddType
	{
		FightParamAddType_Base = 0,
		FightParamAddType_Extra,
		FightParamAddType_Percent,
	};

	struct FightParamKV
	{
		FightParamKV() {}
		FightParamKV(FightParamAddType _add_type, NetProto::EFightParam _key, int _val, int _unique_key);
		
		FightParamAddType add_type = FightParamAddType_Base;
		NetProto::EFightParam key = NetProto::EFP_None;
		int val = 0;
		int unique_id = 0;

		void Attach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const;
		void Deattach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const;
	};

	struct FightParamKVs
	{
		std::vector<FightParamKV> kvs;
		void Attach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const;
		void Deattach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const;
	};

	class EffectAttrsConfig : public EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const;

	public:
		bool InitCfg(const Config::CsvEffectAttrsConfig *csv_cfg);
		int GetHoldTime() const { return m_hold_time_ms; }
		int GetUniqueId() const { return m_unique_id; }
		const FightParamKVs & GetFightParamKvs() const { return m_fight_params; }

	protected:
		int m_hold_time_ms = 0;
		int m_unique_id = 0;
		FightParamKVs m_fight_params;
	};
}
