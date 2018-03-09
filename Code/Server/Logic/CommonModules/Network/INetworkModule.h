#pragma once

#include "INetworkHandler.h"
#include "ModuleDef/IModule.h"
#include <string>
#include <functional>

class INetworkModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Network;
	INetworkModule(ModuleMgr *module_mgr) : IModule(module_mgr , MODULE_NAME) {}
	virtual ~INetworkModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

public:
	virtual NetId Listen(std::string ip, uint16_t port,  void *opt, std::weak_ptr<INetListenHander> handler) = 0;
	virtual NetId Connect(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler) = 0;
	virtual void Close(NetId netid) = 0;
	virtual int64_t ListenAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetListenHander> handler) = 0;
	virtual int64_t ConnectAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler) = 0;
	virtual void CancelAsync(uint64_t async_id) = 0;
	virtual bool Send(NetId netId, char *buffer, uint32_t len) = 0;
};

