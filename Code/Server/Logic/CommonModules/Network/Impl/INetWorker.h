#pragma once
#include "CommonModules/Network/Impl/NetworkModule.h"

namespace Net
{
	class INetWorker
	{
	public:
		INetWorker() {}
		virtual ~INetWorker() {}
		virtual bool AddCnn(NetId id, int fd, std::weak_ptr<INetworkHandler> handler) = 0;
		virtual void RemoveCnn(NetId id) = 0;
		virtual bool Send(NetId netId, char *buffer, uint32_t len) = 0;
		virtual bool GetNetDatas(std::queue<NetWorkData, std::deque<NetWorkData, StlAllocator<NetWorkData>>> *&out_datas) = 0;
		virtual bool Start() = 0;
		virtual void Stop() = 0;
	};
}