#pragma once

#include "Modules/IModule.h"
#include <stdint.h>
#include <string>
#include <functional>

using NetId = uint64_t;

enum ENetworkHandlerType
{
	ENetworkHandler_Connect,
	ENetworkHandler_Listen,
	ENetworkHandlerType_Max,
};

class NetworkHandler
{
public:
	NetworkHandler(ENetworkHandlerType handler_type) : m_handler_type(handler_type) {}
	virtual ~NetworkHandler() {}
	virtual void OnError(NetId netid, int errnu) = 0;
	virtual void OnSucc(NetId netid) = 0;
	virtual void OnClose(NetId netid) = 0;
	ENetworkHandlerType HandlerType() { return m_handler_type; }

protected:
	ENetworkHandlerType m_handler_type;
};
class NetConnectHander : public NetworkHandler
{
public:
	NetConnectHander() : NetworkHandler(ENetworkHandler_Connect) {}
	virtual ~NetConnectHander() {}
	virtual void OnRecvData(NetId netid, char *data, uint32_t len) = 0;
};
class NetListenHander : public NetworkHandler
{
public:
	NetListenHander() : NetworkHandler(ENetworkHandler_Listen) {}
	virtual ~NetListenHander() {}
	virtual void OnNewConnect(NetId netid) = 0;
	virtual std::shared_ptr<NetConnectHander> GenConnectorHandler() = 0;
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
	virtual NetId Listen(std::string ip, uint16_t port,  void *opt, std::weak_ptr<NetListenHander> handler) = 0;
	virtual NetId Connect(std::string ip, uint16_t port, void *opt, std::weak_ptr<NetConnectHander> handler) = 0;
	virtual void Close(NetId netid) = 0;
	virtual int64_t ListenAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<NetListenHander> handler,
		std::function<void(NetId, int)> retCb) = 0;
	virtual int64_t ConnectAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<NetConnectHander> handler,
		std::function<void(NetId, int)> retCb) = 0;
	virtual void CancelAsync(uint64_t async_id) = 0;
	virtual bool Send(NetId netId, char *buffer, uint32_t len) = 0;
};
