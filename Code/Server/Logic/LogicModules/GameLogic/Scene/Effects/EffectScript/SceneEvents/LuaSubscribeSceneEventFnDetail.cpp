#include "LuaSubscribeSceneEventFnDetail.h"

namespace GameLogic
{
	std::vector<LuaScribeSceneEventFnDetail *> LuaScribeSceneEventFnDetail::s_allFnDetails({
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange(),
	});
}