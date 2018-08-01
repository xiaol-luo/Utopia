#pragma once

#include "LuaScribeEventFnDetail.h"

namespace GameLogic
{
	
	class LuaScribeSceneEventFnDetail : public LuaScribeEventFnDetail
	{
	public :
		virtual int GetEventId() = 0;
		virtual FnDoSubscribeEvent GetSubscribeEventFn() = 0;
		virtual std::string GetLuaFunName() = 0;
		static std::vector<LuaScribeEventFnDetail *> s_allFnDetails;
	};

	/// sol_ignore
	class LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange : public LuaScribeSceneEventFnDetail { LuaScribeSceneEventFnDetail_ClassBody; };
}