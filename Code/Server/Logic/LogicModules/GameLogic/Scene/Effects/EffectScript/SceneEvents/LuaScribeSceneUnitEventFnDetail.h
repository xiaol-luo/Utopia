#pragma once

#include "LuaScribeSceneEventFnDetail.h"

namespace GameLogic
{
	class LuaScribeSceneUnitEventFnDetail : public LuaScribeEventFnDetail
	{
	public:
		virtual int GetEventId() = 0;
		virtual FnDoSubscribeEvent GetSubscribeEventFn() = 0;
		static std::vector<LuaScribeEventFnDetail *> s_allFnDetails;
	};

	/// sol_ignore
	struct LuaScribeSceneUnitEventFnParam
	{
		std::shared_ptr<SceneUnit> su;
	};

	/// sol_ignore
	class LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange : public LuaScribeSceneUnitEventFnDetail { LuaScribeSceneUnitEventFnDetail_ClassBody; };
}