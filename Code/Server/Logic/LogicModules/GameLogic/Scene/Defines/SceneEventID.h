#pragma once

// 场景单位事件
enum ESUEventId
{
	ESU_PosChange = 0,				// 位置改变
	ESU_EnterScene,					// 进入场景
	ESU_LeaveScene,					// 离开场景
	ESU_VolecityChange,				// su速度改变
	ESU_MoveStateChange,			// su移动状态改变
	ESU_FightParamChange,			// 战斗参数变了
	ESU_DizzinessChange,			// su昏迷状态改变 true:atttach,  false:deattach
	ESU_ImmobilizedChange,			// su定身状态改变 true:atttach,  false:deattach
	ESU_BlindChange,				// su致盲状态改变 true:atttach,  false:deattach
	ESU_SilenceChange,				// su沉默状态改变 true:atttach,  false:deattach
	ESU_DeadChange,					// su死亡状态改变 true:atttach,  false:deattach

	ES_ReloadConfig,				// 重载了配置
	ES_TestHeartBeat,				// 测试用
};