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
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"

namespace GameLogic
{
	TestScene::TestScene(GameLogicModule * logic_module) : NewScene(logic_module)
	{
	}

	TestScene::~TestScene()
	{
	}

	bool TestScene::OnAwake()
	{
		assert(m_game_logic->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec.size() > 0);
		m_sceneCfg = m_game_logic->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec[0];

		this->AddModule(new SceneMove());
		this->AddModule(new SceneView());
		this->AddModule(new SceneNavMesh());

		m_ev_dispacher->Subscribe(ES_TestHeartBeat, std::bind(&TestScene::TestAction, this));

		m_test_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, this));
		m_test_ticker.SetCd(1);
		return true;
	}

	void BuildHero(std::shared_ptr<SceneUnit> su, NewScene *scene, 
		Vector3 pos, EViewCamp view_camp)
	{
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
		}
		{
			auto sum = su->AddModule(std::make_shared<SceneUnitMove>());
		}
		{
			auto suf = su->AddModule(std::make_shared<SceneUnitFightParam>());
		}
	}

	bool TestScene::OnLateAwake()
	{
		red_su = std::make_shared<SceneUnit>();
		BuildHero(red_su, this, Vector3(50, 0, 50), EViewCamp_Red);
		this->AddUnit(red_su);

		blue_su = std::make_shared<SceneUnit>();
		BuildHero(blue_su, this, Vector3(50, 0, 50), EViewCamp_Blue);
		this->AddUnit(blue_su);

		return true;
	}

	void TestScene::OnLateUpdate()
	{
		this->GetEvDispacher()->Fire(ES_TestHeartBeat);
	}

	void TestScene::TestAction()
	{
		if (!m_test_ticker.InCd())
		{
			m_test_ticker.Restart();
			if (m_scene_units.size() < 10)
			{
				auto hero = std::make_shared<SceneUnit>();
				BuildHero(hero, this, Vector3(std::rand() % 100, 0, std::rand() % 100), (EViewCamp)(std::rand() % 2));
				this->AddUnit(hero);
			}
		}
	}
}

