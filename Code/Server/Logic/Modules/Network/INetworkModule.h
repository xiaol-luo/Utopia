#pragma once

#include "Modules/IModule.h"
#include <stdint.h>
#include <string>
#include <functional>

using NetId = uint64_t;

class NetworkHandler
{
	virtual void OnError(NetId net_id, int errnu) = 0;
	virtual void OnSucc(NetId net_id) = 0;
};
class NetConnectHander : public NetworkHandler
{
	virtual void OnRecvData(NetId net_id, char *data, uint32_t len) = 0;
};
class NetListenHander : public NetworkHandler
{
	virtual void OnNewConnect(NetId netid) = 0;
	virtual void OnCloseConnect(NetId net_id) = 0;
	virtual NetConnectHander * GenConnectorHandler() = 0;
};

class INetworkModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Network;
	INetworkModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr , MODULE_NAME) {}
	virtual ~INetworkModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

public:
	virtual NetId Listen(std::string ip, uint16_t port,  std::weak_ptr<NetListenHander> handler) = 0;
	virtual NetId Connect(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler) = 0;
	virtual void Close(NetId net_id) = 0;
	virtual int64_t ListenAsync(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler,
		std::function<void(NetId, int)> retCb) = 0;
	virtual int64_t ConnectAsync(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler,
		std::function<void(NetId, int)> retCb) = 0;
	virtual void CancelAsync(uint64_t async_id) = 0;
	virtual bool Send(NetId netId, char *buffer, uint32_t len) = 0;
};
