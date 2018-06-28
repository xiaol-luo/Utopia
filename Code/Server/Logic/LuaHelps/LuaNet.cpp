#include "LuaNet.h"

#include "Common/Macro/ServerLogicMacro.h"
#include "Network/Utils/NetworkAgent.h"

#include "network/Protobuf/try.pb.h"

namespace LuaNet
{
	bool SendBuffer(NetId netid, int protocol_id, const std::string &msg)
	{
		if (nullptr == server_logic)
			return false;
		NetworkAgent *net_agent = server_logic->GetNetAgent();
		if (nullptr == net_agent)
			return false;
		bool ret = GlobalServerLogic->GetNetAgent()->Send(netid, protocol_id, (char *)msg.c_str(), (uint32_t)msg.size());
		return ret;
	}
}
