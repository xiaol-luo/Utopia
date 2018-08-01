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
	/// sol_ignore
	class LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange : public LuaScribeSceneEventFnDetail 
	{ 
		LuaScribeSceneEventFnDetail_ClassBody; 
		LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange(int _event_id, std::string _lua_fn_name) { event_id = _event_id; lua_fn_name = _lua_fn_name; }
		int event_id;
		std::string lua_fn_name;
	};
	/// sol_ignore
	class LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange : public LuaScribeSceneEventFnDetail
	{
		LuaScribeSceneEventFnDetail_ClassBody;
		LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange(int _event_id, std::string _lua_fn_name) { event_id = _event_id; lua_fn_name = _lua_fn_name; }
		int event_id;
		std::string lua_fn_name;
	};
}