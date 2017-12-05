#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

class AIHero;

namespace GameLogic
{
	class SceneHeroAction : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Action;
	public:
		SceneHeroAction();
		virtual ~SceneHeroAction() override;

	protected:
		virtual void OnAwake() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	protected:
		AIHero *m_bt_agent;
	};
}

