#pragma once


namespace GameLogic
{
	enum SyncClientMsgFilter
	{
		SCMF_All = -1,
		SCMF_ForInit = 1 << 0,
		SCMF_ForMutable = 1 << 1,
	};

	const static float MOVE_TO_POS_IGNORE_SQR_DISTANCE = 0.01f;
}
