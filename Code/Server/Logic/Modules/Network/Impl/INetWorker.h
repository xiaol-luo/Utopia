#pragma once
#include "Modules/Network/Impl/NetworkModule.h"

namespace Net
{
	class INetWorker
	{
	public:
		INetWorker() {}
		virtual ~INetWorker() {}
		virtual bool AddCnn(NetId id, int fd, std::weak_ptr<INetworkHandler> handler) = 0;
		virtual void RemoveCnn(NetId id) = 0;
		virtual bool GetNetDatas(std::queue<NetWorkData> *&out_datas) = 0;
		virtual bool Start() = 0;
		virtual void Stop() = 0;
	};
}