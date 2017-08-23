#pragma once
#include <stdint.h>

using NetId = uint64_t;

namespace Net
{
	// 长度描述所用字节数
	static const int PROTOCOL_LEN_DESCRIPT_SIZE = sizeof(uint32_t);
}
