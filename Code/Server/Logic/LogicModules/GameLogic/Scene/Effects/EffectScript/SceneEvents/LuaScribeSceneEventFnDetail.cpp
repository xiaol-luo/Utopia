#include "LuaScribeSceneEventFnDetail.h"

namespace GameLogic
{
	std::vector<LuaScribeEventFnDetail *> LuaScribeSceneEventFnDetail::s_allFnDetails({
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange(),
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange(ESU_DizzinessChange, "OnDizzinessChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange(ESU_ImmobilizedChange, "OnImmobilizedChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange(ESU_BlindChange, "OnBlindChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange(ESU_SilenceChange, "OnSilenceChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange(ESU_DeadChange, "OnDeadChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange(ESU_HpChange, "OnHpChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange(ESU_MpChange, "OnMpChange"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitPosChange(),
		new LuaScribeSceneEventFnDetail_OnSceneUnitEnterLeaveScene(ESU_EnterScene, "OnEnterScene"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitEnterLeaveScene(ESU_LeaveScene, "OnLeaveScene"),
		new LuaScribeSceneEventFnDetail_OnSceneUnitVolecityChange(),
		new LuaScribeSceneEventFnDetail_OnSceneUnitMoveStateChange(),
	});
}