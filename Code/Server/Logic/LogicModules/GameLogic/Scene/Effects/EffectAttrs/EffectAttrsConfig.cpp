#include "EffectAttrsConfig.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"
#include "EffectAttrs.h"

namespace std
{
	template<>
	struct hash<NetProto::EFightParam>
	{
		typedef NetProto::EFightParam argument_type;
		typedef std::size_t result_type;

		result_type operator()(argument_type const &s) const
		{
			return (result_type)s;
		}
	};
}

namespace GameLogic
{
	FightParamKV::FightParamKV(FightParamAddType _add_type, NetProto::EFightParam _key, int _val, int _unique_key)
		: add_type(_add_type), key(_key), val(_val), unique_id(_unique_key)
	{
	}

	void FightParamKV::Attach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const
	{
		switch (add_type)
		{
		case FightParamAddType_Base:
		{
			su_fp->AddBaseValue(key, val, is_recal, unique_id);
		}
		break;
		case FightParamAddType_Extra:
		{
			su_fp->AddExtraValue(key, val, is_recal, unique_id);
		}
		break;
		case FightParamAddType_Percent:
		{
			su_fp->AddExtraPercent(key, val, is_recal, unique_id);
		}
		break;
		}
	}

	void FightParamKV::Deattach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const
	{
		switch (add_type)
		{
		case FightParamAddType_Base:
		{
			su_fp->RemoveBaseValue(key, val, unique_id);
		}
		break;
		case FightParamAddType_Extra:
		{
			su_fp->RemoveExtraValue(key, val, unique_id);
		}
		break;
		case FightParamAddType_Percent:
		{
			su_fp->RemoveExtraPercent(key, val, unique_id);
		}
		break;
		}
	}

	void FightParamKVs::Attach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const
	{
		if (nullptr == su_fp)
			return;

		std::unordered_set<NetProto::EFightParam> efps;
		for (auto &&item : kvs)
		{
			item.Attach(su_fp, false);
			efps.insert(item.key);
		}
		if (is_recal)
		{
			for (NetProto::EFightParam efp : efps)
			{
				su_fp->Recal(efp, true);
			}
		}
	}

	void FightParamKVs::Deattach(std::shared_ptr<SceneUnitFightParam> su_fp, bool is_recal) const
	{
		if (nullptr == su_fp)
			return;

		std::unordered_set<NetProto::EFightParam> efps;
		for (auto &&item : kvs)
		{
			item.Deattach(su_fp, false);
			efps.insert(item.key);
		}
		if (is_recal)
		{
			for (NetProto::EFightParam efp : efps)
			{
				su_fp->Recal(efp, true);
			}
		}
	}

	std::shared_ptr<EffectBase> EffectAttrsConfig::CreateEffect(SceneEffects * scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectAttrs>(this, scene_effects, effect_key);
	}

	bool EffectAttrsConfig::InitCfg(const Config::CsvEffectAttrsConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		m_unique_id = csv_cfg->unique_id;
		m_hold_time_ms = csv_cfg->hold_time_ms;
		m_reversible = m_hold_time_ms > 0;

		for (const std::vector<int> &attr_cfg : csv_cfg->base_attrs)
		{
			assert(attr_cfg.size() >= 2);
			m_fight_params.kvs.push_back(FightParamKV(
				FightParamAddType_Base,
				(NetProto::EFightParam)attr_cfg[0], attr_cfg[1],
				attr_cfg.size() > 2 ? attr_cfg[2] : 0
			));
		}
		for (const std::vector<int> &attr_cfg : csv_cfg->extra_attrs)
		{
			assert(attr_cfg.size() >= 2);
			m_fight_params.kvs.push_back(FightParamKV(
				FightParamAddType_Extra,
				(NetProto::EFightParam)attr_cfg[0], attr_cfg[1],
				attr_cfg.size() > 2 ? attr_cfg[2] : 0
			));
		}
		for (const std::vector<int> &attr_cfg : csv_cfg->percent_attrs)
		{
			assert(attr_cfg.size() >= 2);
			m_fight_params.kvs.push_back(FightParamKV(
				FightParamAddType_Percent,
				(NetProto::EFightParam)attr_cfg[0], attr_cfg[1],
				attr_cfg.size() > 2 ? attr_cfg[2] : 0
			));
		}

		return true;
	}
}