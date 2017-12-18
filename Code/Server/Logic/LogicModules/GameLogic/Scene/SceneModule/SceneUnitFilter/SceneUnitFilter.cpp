#include "SceneUnitFilter.h"

namespace GameLogic
{
	SceneUnitFilter::SceneUnitFilter() : SceneModule(MODULE_TYPE)
	{

	}

	SceneUnitFilter::~SceneUnitFilter()
	{

	}

	std::unordered_set<std::shared_ptr<SceneUnit>> SceneUnitFilter::FilterSceneUnit(EffectFilterOption filter_option)
	{
		std::unordered_set<std::shared_ptr<SceneUnit>> ret_sus = std::unordered_set<std::shared_ptr<SceneUnit>>();


		return ret_sus;
	}

	bool SceneUnitFilter::OnAwake()
	{
		return true;
	}

	void SceneUnitFilter::OnUpdate()
	{
	}
}
