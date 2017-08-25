#pragma once

namespace GameLogic
{
	enum PlayerMsgProtocol
	{
		PlayerMsgProtocol_Invalid = 0,
		PlayerMsgProtocol_Ping,
		PlayerMsgProtocol_Pong,

		PlayerMsgProtocol_Max,
	};
}