#include "LuaNet.h"

#include "Common/Macro/AllMacro.h"
#include "ServerLogics/ServerLogic.h"
#include "Network/Utils/NetworkAgent.h"


namespace LuaNet
{
	bool SendBuffer(NetId netid, int protocol_id, const std::string &msg)
	{
		if (nullptr == server_logic)
			return false;
		NetworkAgent *net_agent = server_logic->GetNetAgent();
		if (nullptr == net_agent)
			return false;
		bool ret = G_NetAgent->Send(netid, protocol_id, (char *)msg.c_str(), (uint32_t)msg.size());
		return ret;
	}
}
