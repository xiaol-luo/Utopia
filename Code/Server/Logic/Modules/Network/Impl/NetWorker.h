#pragma once

#include <memory>
#include <queue>
#include <unordered_map>
#include <set>
#include <mutex>
#include "Modules/Network/Impl/NetworkModule.h"

namespace Net
{
	class INetWorker
	{
	public:
		INetWorker() {}
		virtual ~INetWorker() {}
		virtual bool AddCnn(NetId id, int fd, std::weak_ptr<NetworkHandler> handler) = 0;
		virtual void RemoveCnn(NetId id) = 0;
		virtual bool GetNetDatas(std::queue<NetWorkData> *&out_datas) = 0;
		virtual bool Start() = 0;
		virtual void Stop() = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	class NetWorker : public INetWorker
	{
	public:
		NetWorker();
		virtual ~NetWorker();
		virtual bool AddCnn(NetId id, int fd, std::weak_ptr<NetworkHandler> handler);
		virtual void RemoveCnn(NetId id);
		virtual bool GetNetDatas(std::queue<NetWorkData> *&out_datas);
		virtual bool Start();
		virtual void Stop();

	protected:
		struct NetConnectionData
		{
			NetConnectionData() {}
			NetConnectionData(NetId _netid, int _fd, std::weak_ptr<NetworkHandler> _handler)
				: netid(_netid), fd(_fd), handler(_handler) {}

			NetId netid = 0;
			int fd = 0;
			std::weak_ptr<NetworkHandler> handler;
			bool is_expired = false;
		};
		std::unordered_map<NetId, NetConnectionData *> m_cnn_datas;
		std::unordered_map<NetId, NetConnectionData *> m_wait_add_cnn_datas;
		std::set<NetId> m_wait_remove_netids;
		std::mutex m_cnn_data_mutex;

		static const int NETWORK_DATA_QUEUE_LEN = 2;
		int m_working_network_data_queue = 0;
		std::queue<NetWorkData> m_network_data_queues[NETWORK_DATA_QUEUE_LEN];
		std::mutex m_network_data_mutex;
	};
}