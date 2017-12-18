#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace GameLogic
{
	class SceneUnitFilter : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE = ESceneModule_UnitFilter;
	public:
		SceneUnitFilter();
		virtual ~SceneUnitFilter() override;

	public:
		std::unordered_set<std::shared_ptr<SceneUnit>> FilterSceneUnit(EffectFilterOption filter_option);

	protected:
		virtual bool OnAwake() override;
		virtual void OnUpdate() override;
	};
}
