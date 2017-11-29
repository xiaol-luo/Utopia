#include "TestScene.h"
#include "SceneModule/SceneMove/SceneMove.h"
#include "SceneModule/SceneView/SceneView.h"
#include "SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/GameLogicModule.h"
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitSight.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitBody.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMove.h"

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
			sub->SetRadius(5);
		}
		{
			auto sum = su->AddModule(std::make_shared<SceneUnitMove>());
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
		int a = 0;
		++a;
	}
}

