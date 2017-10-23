#include "NetworkUtil.h"

INetworkModule * NetworkUtil::module = nullptr;

bool NetworkUtil::Init(INetworkModule * _module)
{
	if (nullptr != module)
		return false;

	module = _module;
	return nullptr != module;
}
