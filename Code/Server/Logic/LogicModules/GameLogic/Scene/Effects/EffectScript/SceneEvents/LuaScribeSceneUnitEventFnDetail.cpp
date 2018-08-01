#include "LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	std::vector<LuaScribeEventFnDetail *> LuaScribeSceneUnitEventFnDetail::s_allFnDetails({
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange(),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange(ESU_DizzinessChange),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange(ESU_ImmobilizedChange),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange(ESU_BlindChange),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange(ESU_SilenceChange),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange(ESU_DeadChange),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitHpMpChange(ES_HpChange),
		new LuaScribeSceneUnitEventFnDetail_OnSceneUnitHpMpChange(ES_MpChange),
	});
}