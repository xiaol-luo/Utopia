#pragma once

#include "NewScene.h"
#include "Common/Utils/Ticker.h"

namespace GameLogic
{
	class TestScene : public NewScene
	{
	public:
		TestScene(GameLogicModule *logic_module);
		virtual ~TestScene() override;

	protected:
		virtual bool OnAwake() override;
		virtual bool OnLateAwake() override;
		virtual void OnLateUpdate() override;

		bool CheckConfigValid();

		void TestAction();
		Ticker m_test_ticker;

	};
}