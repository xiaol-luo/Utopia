#pragma once

#include "LuaScribeSceneEventFnDetail.h"

namespace GameLogic
{
	class LuaScribeSceneUnitEventFnDetail : public LuaScribeEventFnDetail
	{
	public:
		virtual int GetEventId() = 0;
		virtual std::string GetLuaFunName() = 0;
		virtual FnDoSubscribeEvent GetSubscribeEventFn() = 0;
		static std::vector<LuaScribeEventFnDetail *> s_allFnDetails;
	};

	struct LuaScribeSceneUnitEventFnParam
	{
		std::shared_ptr<SceneUnit> su;
		sol::object lua_param = sol::nil;
	};

	/// sol_ignore
	class LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange : public LuaScribeSceneEventFnDetail { LuaScribeSceneEventFnDetail_ClassBody; };
}