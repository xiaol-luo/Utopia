#pragma once

#include "CommonModules/Network/INetworkModule.h"

class NetworkUtil
{
public:
	static bool Init(INetworkModule *_module);
	static void Destroy() { module = nullptr; }

public:

private:
	static INetworkModule *module;
};
