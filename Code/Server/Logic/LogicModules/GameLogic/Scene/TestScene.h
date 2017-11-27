#pragma once

#include "NewScene.h"

namespace GameLogic
{
	class TestScene : public NewScene
	{
	public:
		TestScene(GameLogicModule *logic_module);
		virtual ~TestScene() override;
		virtual Config::CsvSceneConfig * GetCfg() override { return m_sceneCfg; }

	protected:
		virtual bool OnAwake() override;
		virtual bool OnLateAwake() override;

		Config::CsvSceneConfig *m_sceneCfg = nullptr;
	};
}