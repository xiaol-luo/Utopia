#pragma once

// 场景单位事件
enum ESUEventId
{
	ESU_PosChange = 0,		// 位置改变
	ESU_EnterScene,			// 进入场景
	ESU_LeaveScene,			// 离开场景
	ESU_VolecityChange,		// su速度改变
	ESU_MoveStateChange,	// su移动状态改变
};