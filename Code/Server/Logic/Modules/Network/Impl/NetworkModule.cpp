#include "NetworkModule.h"

NetworkModule::NetworkModule(std::shared_ptr<ModuleMgr> module_mgr) : INetworkModule(module_mgr)
{

}

NetworkModule::~NetworkModule()
{

}

EModuleRetCode NetworkModule::Init(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Awake()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Update()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Destroy()
{
	return EModuleRetCode_Succ;
}

NetId NetworkModule::Listen(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler)
{
	return 0;
}

NetId NetworkModule::Connect(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler)
{
	return 0;
}

void NetworkModule::Close(NetId net_id)
{
}

int64_t NetworkModule::ListenAsync(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler,
	std::function<void(NetId, int)> retCb)
{
	return 0;
}

int64_t NetworkModule::ConnectAsync(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler,
	std::function<void(NetId, int)> retCb)
{
	return 0;
}

void NetworkModule::CancelAsync(uint64_t async_id)
{

}

bool NetworkModule::Send(NetId netId, char *buffer, uint32_t len)
{
	return 0;
}

