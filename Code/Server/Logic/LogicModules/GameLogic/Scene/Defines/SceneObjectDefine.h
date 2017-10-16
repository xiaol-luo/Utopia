#pragma once


namespace GameLogic
{
	enum  EMoveAgentState
	{
		EMoveAgentState_Idle = 0,
		EMoveAgentState_MoveToPos,
		EMoveAgentState_MoveToDir,
		EMoveAgentState_Immobilized,
		EMoveAgentState_ForceLine,
		EMoveAgentState_ForceSky,

		EMoveAgentState_Max,
	};

	enum EMoveState
	{
		EMoveState_Idle = 0,
		EMoveState_Move,
		EMoveState_Immobilized,
		EMoveState_ForceMove,
	};
}
