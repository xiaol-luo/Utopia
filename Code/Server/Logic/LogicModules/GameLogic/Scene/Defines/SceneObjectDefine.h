#pragma once


namespace GameLogic
{
	enum EMoveType
	{
		EMoveType_None = 1 << 0,
		EMoveType_Pos = 1 << 2,
		EMoveType_Dir = 1 << 3,
		EMoveType_ForceMovePos = 1 << 4,
		EMoveType_ForceMoveDir = 1 << 5,

		EMoveType_Max,
	};

	enum ESceneObjectState
	{
		ESOS_Idle = 0,
		ESOS_Move,
		ESOS_ForceMove,
	};
}
