#pragma once


namespace GameLogic
{
	/*
	enum  EMoveAgentState
	{
		EMoveAgentState_Idle = 0,
		EMoveAgentState_MoveToPos,
		EMoveAgentState_MoveToDir,
		EMoveAgentState_Immobilized,
		EMoveAgentState_ForceLine,
		EMoveAgentState_ForcePos,

		EMoveAgentState_Max,
	};

	enum EMoveState
	{
		EMoveState_Idle = 0,
		EMoveState_Move,
		EMoveState_Immobilized,
		EMoveState_ForceMove,
	};
	*/

	enum SyncClientMsgFilter
	{
		SCMF_All = -1,
		SCMF_ForInit = 1 << 0,
		SCMF_ForMutable = 1 << 1,
	};
}
