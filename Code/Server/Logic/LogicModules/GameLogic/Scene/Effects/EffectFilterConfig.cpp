#include "EffectFilterConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include <assert.h>
#include "Network/Protobuf/BattleEnum.pb.h"
#include "Utils/ConfigUtil.h"
#include <sol.hpp>

namespace GameLogic
{

	// EEffectFilterLimitNumPriority
	static std::unordered_map<std::string, EEffectFilterLimitNumPriority> Limit_Num_Prioriry_Map ({
		{ "near_caster", EEffectFilterLimitNumPriority_NearCaster },
		{ "away_caster", EEffectFilterLimitNumPriority_AwayCaster },
		{ "near_target", EEffectFilterLimitNumPriority_NearTarget },
		{ "away_target", EEffectFilterLimitNumPriority_AwayTarget },
		{ "", EEffectFilterLimitNumPriority_None},
	});
	EEffectFilterLimitNumPriority ConvertEEffectFilterLimitNumPriority(std::string val)
	{
		return ConfigUtil::ConvertUtil(Limit_Num_Prioriry_Map, val);
	}

	// EsceneUnitType
	static std::unordered_map<std::string, NetProto::ESceneUnitType> UNIT_TYPES_MAP({
		{ "hero", NetProto::EsceneUnitType_Hero },
		{ "monster", NetProto::EsceneUnitType_Monster },
		{ "soldier", NetProto::EsceneUnitType_Soldier },
		{ "building", NetProto::EsceneUnitType_Building },
		{ "effect", NetProto::EsceneUnitType_Effect },
	});
	NetProto::ESceneUnitType ConvertSceneUnitType(std::string val)
	{
		return ConfigUtil::ConvertUtil(UNIT_TYPES_MAP, val);
	}
	uint64_t ConvertESceneUnitTypes(std::string val)
	{
		uint64_t ret = 0;
		std::vector<std::string> unit_types;
		assert(ConfigUtil::Str2Vec(val, unit_types));
		for (std::string &unit_type : unit_types)
		{
			ret |= uint64_t(1) << ConvertSceneUnitType(unit_type);
		}
		return ret;
	}

	// EEffectFilterRelation
	std::unordered_map<std::string, NetProto::ESceneUnitRelation> Effect_Relation_Map({
		{ "self", NetProto::ESceneUnitRelation::ESceneUnitRelation_Self },
		{ "friend", NetProto::ESceneUnitRelation::ESceneUnitRelation_Friend },
		{ "enemy", NetProto::ESceneUnitRelation::ESceneUnitRelation_Enemy },
	});
	int ConvertERelations(std::string val)
	{
		int ret = 0;
		std::vector<std::string> relation_vals;
		assert(ConfigUtil::Str2Vec(val, relation_vals));
		for (std::string &relation_val : relation_vals)
		{
			ret |= 1 << ConfigUtil::ConvertUtil(Effect_Relation_Map, relation_val);
		}
		return ret;
	}

	bool EffectFilterConfig::InitCfg(Config::CsvEffectFilterConfig * csv_cfg)
	{
		id = csv_cfg->id;
		limit_num = csv_cfg->limit_num;
		limit_num_priority = ConfigUtil::ConvertUtil(Limit_Num_Prioriry_Map, csv_cfg->limit_num_priority);
		unit_types = ConvertESceneUnitTypes(csv_cfg->unit_types);
		relations = ConvertERelations(csv_cfg->relations);
		anchor = StrToEffectFilterAnchor(csv_cfg->anchor);

		if (csv_cfg->shape_circle > 0)
		{
			shape = EEffectFilterShape_Circle;
			shape_param.circle.radius = csv_cfg->shape_circle;
		}
		else if (!csv_cfg->shape_rect.empty())
		{
			assert(2 == csv_cfg->shape_rect.size());
			shape = EEffectFilterShape_Rect;
			shape_param.rect.x_size = csv_cfg->shape_rect[0];
			shape_param.rect.y_size = csv_cfg->shape_rect[1];
		}
		else if (!csv_cfg->shape_sector.empty())
		{
			assert(2 == csv_cfg->shape_sector.size());
			shape = EEffectFilterShape_Sector;
			shape_param.sector.radius = csv_cfg->shape_sector[0];
			shape_param.sector.angle = csv_cfg->shape_sector[1];
		}

		assert(EEffectFilterShape_None != shape);
		return true;
	}

	EffectFilterConfigMgr::EffectFilterConfigMgr()
	{

	}

	EffectFilterConfigMgr::~EffectFilterConfigMgr()
	{
		for (auto kv_pair : m_filter_cfgs)
		{
			delete kv_pair.second;
		}
		m_filter_cfgs.clear();
	}

	bool EffectFilterConfigMgr::LoadCfg(Config::CsvConfigSets * csv_cfgs, void ** param)
	{
		if (nullptr == param)
		{
			for (Config::CsvEffectFilterConfig *item : csv_cfgs->csv_CsvEffectFilterConfigSet->cfg_vec)
			{
				EffectFilterConfig *cfg = new EffectFilterConfig();
				assert(cfg->InitCfg(item));
				auto ret = m_filter_cfgs.insert(std::make_pair(cfg->id, cfg));
				assert(ret.second);
			}
		}
		else
		{
			sol::table su_filter_tb = *(sol::table *)param;
			for (auto kv_pair : su_filter_tb)
			{
				sol::object key_obj = kv_pair.first;
				sol::object val_obj = kv_pair.second;

				if (val_obj.is<sol::table>())
				{
					sol::table skill_json = val_obj.as<sol::table>();
					auto new_cfg = new EffectFilterConfig();

					new_cfg->id = skill_json["id"];
					new_cfg->name = skill_json["name"];
					new_cfg->limit_num = skill_json["limit_num"];
					new_cfg->limit_num_priority = skill_json["limit_num_priority"];
					new_cfg->unit_types = skill_json["unit_type_flag"];
					new_cfg->relations = skill_json["relation_flag"];
					new_cfg->anchor = skill_json["anchor"];
					new_cfg->shape = skill_json["shape_type"];
					new_cfg->shape_param.circle.radius = skill_json["shape_circle"];
					new_cfg->shape_param.rect.x_size = skill_json["shape_rect"]["x"];
					new_cfg->shape_param.rect.y_size = skill_json["shape_rect"]["y"];
					new_cfg->shape_param.sector.radius = skill_json["shape_sector"]["x"];
					new_cfg->shape_param.sector.angle = skill_json["shape_sector"]["y"];
					auto ret = m_filter_cfgs.insert(std::make_pair(new_cfg->id, new_cfg));
					assert(ret.second);
				}
			}
		}


		return true;
	}

	const EffectFilterConfig * EffectFilterConfigMgr::GetCfg(int id)
	{
		auto it = m_filter_cfgs.find(id);
		if (m_filter_cfgs.end() != it)
			return it->second;
		return nullptr;
	}
}