#include "LuaScribeSceneEventFnDetail.h"

namespace GameLogic
{
	std::vector<LuaScribeEventFnDetail *> LuaScribeSceneEventFnDetail::s_allFnDetails({
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange(),
	});
}