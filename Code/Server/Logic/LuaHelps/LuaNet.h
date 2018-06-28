#pragma once

#include "Common/Define/NetworkDefine.h"
#include <string>

namespace LuaNet
{
	bool SendBuffer(NetId netid, int protocol_id, const std::string &msg);
}
