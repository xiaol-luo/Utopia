#include "TestScene.h"
#include "SceneModule/SceneMove/SceneMove.h"
#include "SceneModule/SceneView/SceneView.h"
#include "SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/GameLogicModule.h"
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "GameLogic/Scene/Defines/ESceneEvent.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"
#include "GameLogic/Scene/Skills/SkillConfig.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/Skills/Skill.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitAction/SceneHeroAction.h"
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"
#include "Network/Protobuf/Battle.pb.h"
#include "GameLogic/Scene/Effects/EffectFilterConfig.h"
#include "Utils/LuaUtils.h"

namespace GameLogic
{
	TestScene::TestScene(GameLogicModule * logic_module, std::string init_param) : NewScene(logic_module, init_param)
	{

	}

	TestScene::~TestScene()
	{
		for (auto item : m_expiredCfg)
		{
			delete item;
		}
		m_expiredCfg.clear();
	}

	bool TestScene::OnAwake()
	{
		bool ret = DoLoadConfig(false);
		if (!ret)
			return false;

		this->AddModule(new SceneMove());
		this->AddModule(new SceneView());
		this->AddModule(new SceneNavMesh());
		this->AddModule(new SceneEffects());
		this->AddModule(new SceneUnitFilter());

		m_ev_dispacher->Subscribe(ES_TestHeartBeat, std::bind(&TestScene::TestAction, this));
		m_ev_dispacher->Subscribe(ES_ReloadConfig, std::bind(&TestScene::DoLoadConfig, this, true));

		m_test_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, this));
		m_test_ticker.SetCd(1);
		return true;
	}

	void BuildHero(std::shared_ptr<SceneUnit> su, NewScene *scene, 
		Vector3 pos, EViewCamp view_camp)
	{
		su->SetUnitType(NetProto::EsceneUnitType_Hero);
		su->GetTransform()->SetLocalPos(pos);
		{
			auto sus = su->AddModule(std::make_shared<SceneUnitSight>());
			sus->SetSceneView(scene->GetModule<SceneView>());
			sus->SetViewCamp(view_camp);
		}
		{
			auto sub = su->AddModule(std::make_shared<SceneUnitBody>());
			sub->SetSceneView(scene->GetModule<SceneView>());
			sub->SetRadius(1);
			sub->CovertRect();
		}
		{
			auto sum = su->AddModule(std::make_shared<SceneUnitMove>());
		}
		{
			auto suf = su->AddModule(std::make_shared<SceneUnitFightParam>());
		}
		{
			auto sus = su->AddModule(std::make_shared<SceneUnitSkills>());
		}
		{
			auto sus = su->AddModule(std::make_shared<SceneHeroAction>());
		}
	}

	bool TestScene::OnLateAwake()
	{
		sol::state_view lsv(LuaUtils::GetState());
		// json config and functions
		sol::table json_cfgs = lsv.get_or<sol::table>("json_configs", sol::lua_nil);
		assert(json_cfgs.valid());
		sol::protected_function fn_get_scene = json_cfgs.get_or<sol::protected_function>("get_scene", sol::lua_nil);
		assert(fn_get_scene.valid());
		sol::protected_function fn_get_su = json_cfgs.get_or<sol::protected_function>("get_su", sol::lua_nil);
		assert(fn_get_su.valid());
		// scene config
		sol::protected_function_result pfr = fn_get_scene(m_init_param);
		assert(pfr.valid());
		assert(sol::type::table == pfr.get_type(0));
		sol::table scene_json_cfg = pfr.get<sol::table>(0);
		assert(scene_json_cfg.valid());
		// red side hero config
		pfr = fn_get_su(scene_json_cfg["red_side_hero"]);
		assert(pfr.valid());
		assert(sol::type::table == pfr.get_type(0));
		sol::table red_su_json_cfg = pfr.get<sol::table>(0);
		assert(red_su_json_cfg.valid());
		// blue side hero config
		pfr = fn_get_su(scene_json_cfg["blue_side_hero"]);
		assert(pfr.valid());
		assert(sol::type::table == pfr.get_type(0));
		sol::table blue_su_json_cfg = pfr.get<sol::table>(0);
		assert(blue_su_json_cfg.valid());
		
		{
			auto red_su = std::make_shared<SceneUnit>();
			red_su->SetCamp(NetProto::ESceneUnitCamp_Red);
			BuildHero(red_su, this, Vector3(50, 0, 50), EViewCamp_Red);
			this->AddUnit(red_su);
			{
				auto sus = red_su->GetModule<SceneUnitSkills>();
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(red_su_json_cfg["q_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_QSlot, NetProto::ESkillBar_Default);
					}
				}
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(red_su_json_cfg["q_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_WSlot, NetProto::ESkillBar_Default);
					}
				}
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(red_su_json_cfg["e_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_QSlot, NetProto::ESkillBar_Default);
					}
				}
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(red_su_json_cfg["r_skill_id"]);
					if(nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_RSlot, NetProto::ESkillBar_Default);
					}
				}
			}
		}
		
		{
			auto blue_su = std::make_shared<SceneUnit>();
			blue_su->SetCamp(NetProto::ESceneUnitCamp_Blue);
			BuildHero(blue_su, this, Vector3(50, 0, 50), EViewCamp_Blue);
			this->AddUnit(blue_su);
			{
				auto sus = blue_su->GetModule<SceneUnitSkills>();
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(blue_su_json_cfg["q_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_QSlot, NetProto::ESkillBar_Default);
					}
				}
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(blue_su_json_cfg["q_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_WSlot, NetProto::ESkillBar_Default);
					}
				}
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(blue_su_json_cfg["e_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_QSlot, NetProto::ESkillBar_Default);
					}
				}
				{
					auto skill_cfg = this->GetCfg()->skill_cfgs->GetSkill(blue_su_json_cfg["r_skill_id"]);
					if (nullptr != skill_cfg)
					{
						auto skill = std::make_shared<Skill>(skill_cfg);
						sus->AddSkill(skill, NetProto::ESS_RSlot, NetProto::ESkillBar_Default);
					}
				}
			}
		}
		return true;
	}

	void TestScene::OnLateUpdate()
	{
		//this->GetEvDispacher()->Fire(ES_TestHeartBeat);
	}

	bool TestScene::CheckConfigValid()
	{
		for (auto &&item : m_cfg->effect_cfg_mgr->GetAllCfg())
		{
			const EffectConfigBase * cfg = item.second;
			int filter_id = cfg->GetFilterId();
			if (filter_id > 0 && nullptr == m_cfg->effect_filter_cfg_mgr->GetCfg(filter_id))
			{
				assert(false);
				return false;
			}
		}
		return true;
	}

	void TestScene::TestAction()
	{
		if (!m_test_ticker.InCd())
		{
			m_test_ticker.Restart();
			if (m_scene_units.size() < 2)
			{
				auto hero = std::make_shared<SceneUnit>();
				BuildHero(hero, this, Vector3(std::rand() % 100, 0, std::rand() % 100), (EViewCamp)(std::rand() % 2));
				this->AddUnit(hero);
			}
		}
	}

	bool TestScene::DoLoadConfig(bool isReload)
	{
		// init config
		SceneAllConfig *newCfg = new SceneAllConfig();
		SceneAllConfig *oldCfg = m_cfg;
		m_cfg = newCfg;
		assert(m_game_logic->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec.size() > 0);
		m_cfg->scene_cfg = m_game_logic->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec[0];
		bool ret = true;

		sol::state_view lsv(LuaUtils::GetState());
		// json config and functions
		sol::table json_cfgs = lsv.get_or<sol::table>("json_configs", sol::lua_nil);
		assert(json_cfgs.valid());

		sol::table skill_json_cfg = json_cfgs["skill"];
		assert(skill_json_cfg.valid());
		sol::table su_filter_json_cfg = json_cfgs["su_filter"];
		assert(su_filter_json_cfg.valid());

		ret = ret & m_cfg->skill_cfgs->LoadCfg(m_game_logic->GetCsvCfgSet(), (void **)&skill_json_cfg);
		ret = ret & m_cfg->effect_cfg_mgr->LoadCfg(m_game_logic->GetCsvCfgSet(), (void **)&json_cfgs);
		ret = ret & m_cfg->effect_filter_cfg_mgr->LoadCfg(m_game_logic->GetCsvCfgSet(), (void **)&su_filter_json_cfg);
		ret = ret & this->CheckConfigValid();
		if (!ret)
		{
			m_cfg = oldCfg;
			delete newCfg; newCfg = nullptr;
		}
		else
		{
			if (nullptr != oldCfg)
				m_expiredCfg.push_back(oldCfg);
			if (isReload)
			{
				auto fn = [this](std::shared_ptr<SceneUnit> su, void *param) {
					std::shared_ptr<SceneUnitSkills> skills = su->GetModule<SceneUnitSkills>();
					if (nullptr != skills)
					{
						auto modifySkillFn = [this](std::shared_ptr<Skill> skill, void *param) {
							skill->ReloadCfg(m_cfg);
						};
						skills->ForeachSkill(modifySkillFn, nullptr);
					}
				};
				this->ForeachSceneUnit(fn, nullptr);
			}
		}
		return ret;
	}
}

