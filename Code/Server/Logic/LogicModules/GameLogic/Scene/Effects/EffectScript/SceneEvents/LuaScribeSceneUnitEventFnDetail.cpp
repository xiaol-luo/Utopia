#include "LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	std::vector<LuaScribeEventFnDetail *> LuaScribeSceneUnitEventFnDetail::s_allFnDetails({
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange(),
	});
}