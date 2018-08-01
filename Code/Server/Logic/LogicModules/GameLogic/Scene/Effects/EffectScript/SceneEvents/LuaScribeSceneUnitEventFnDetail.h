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
	/// sol_ignore
	class LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange : public LuaScribeSceneUnitEventFnDetail 
	{
		LuaScribeSceneUnitEventFnDetail_ClassBody;
		LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange(int _event_id) { event_id = _event_id; }
		int event_id;
	};
	/// sol_ignore
	class LuaScribeSceneUnitEventFnDetail_OnSceneUnitHpMpChange : public LuaScribeSceneUnitEventFnDetail
	{
		LuaScribeSceneUnitEventFnDetail_ClassBody;
		LuaScribeSceneUnitEventFnDetail_OnSceneUnitHpMpChange(int _event_id) { event_id = _event_id; }
		int event_id;
	};
	
}