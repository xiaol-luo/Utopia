#pragma once


namespace GameLogic
{
	enum SyncClientMsgFilter
	{
		SCMF_All = -1L,
		SCMF_ForInit = 1L << 0,
		SCMF_ForMove = 1L << 1,
		SCMF_ForCastSkill = 1L << 2,
		SCMF_AllButInit = SCMF_All ^ SCMF_ForInit,
	};

	const static float MOVE_TO_POS_IGNORE_SQR_DISTANCE = 0.01f;
}
