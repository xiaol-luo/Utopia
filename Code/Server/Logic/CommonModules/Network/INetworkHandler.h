#pragma once

#include "Common/Define/NetworkDefine.h"
#include <memory>

enum ENetworkHandlerType
{
	ENetworkHandler_Connect,
	ENetworkHandler_Listen,
	ENetworkHandlerType_Max,
};

class INetworkHandler
{
public:
	INetworkHandler(ENetworkHandlerType handler_type) : m_handler_type(handler_type) {}
	virtual ~INetworkHandler() {}
	virtual void OnClose(int err_num) = 0;
	virtual void OnOpen(int err_num) = 0;
	ENetworkHandlerType HandlerType() { return m_handler_type; }
	NetId GetNetId() { return m_netid; }
	void SetNetId(NetId netid) { m_netid = netid; }

protected:
	ENetworkHandlerType m_handler_type = ENetworkHandlerType_Max;
	NetId m_netid = 0;
};
class INetConnectHander : public INetworkHandler
{
public:
	INetConnectHander() : INetworkHandler(ENetworkHandler_Connect) {}
	virtual ~INetConnectHander() {}
	virtual void OnRecvData(char *data, uint32_t len) = 0;
};
class INetListenHander : public INetworkHandler
{
public:
	INetListenHander() : INetworkHandler(ENetworkHandler_Listen) {}
	virtual ~INetListenHander() {}
	virtual std::shared_ptr<INetConnectHander> GenConnectorHandler(NetId netid) = 0;
};

