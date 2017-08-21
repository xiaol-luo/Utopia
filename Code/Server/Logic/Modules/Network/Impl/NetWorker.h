#pragma once

#include <memory>
#include <queue>
#include <unordered_map>
#include <set>
#include <mutex>
#include "INetWorker.h"
#include "event2/util.h"

struct bufferevent;
struct evconnlistener;
struct event_base;

namespace Net
{
	class NetWorker : public INetWorker
	{
	public:
		NetWorker();
		virtual ~NetWorker();
		virtual bool AddCnn(NetId id, int fd, std::weak_ptr<INetworkHandler> handler);
		virtual void RemoveCnn(NetId id);
		virtual bool GetNetDatas(std::queue<NetWorkData> *&out_datas);
		virtual bool Start();
		virtual void Stop();

	protected:
		virtual void Loop();
		void PushNetworkData(const NetWorkData &data);
	protected:
		struct NetConnectionData
		{
			NetConnectionData() {}
			NetConnectionData(NetWorker *_networker, NetId _netid, int _fd, std::weak_ptr<INetworkHandler> _handler)
				: netid(_netid), fd(_fd), handler(_handler), net_worker(_networker) {}

			NetId netid = 0;
			int fd = 0;
			std::weak_ptr<INetworkHandler> handler;
			bool is_expired = false;
			bufferevent *buffer_ev = nullptr;
			evconnlistener *listen_ev = nullptr;
			NetWorker *net_worker = nullptr;
		};
		std::unordered_map<NetId, NetConnectionData *> m_cnn_datas;
		std::unordered_map<NetId, NetConnectionData *> m_wait_add_cnn_datas;
		std::set<NetId> m_wait_remove_netids;
		std::mutex m_cnn_data_mutex;
		std::set<NetId> m_internal_wait_remove_netids;
		void CheckAddCnnDatas(event_base *base);
		void CheckRemoveCnnDatas();

		static const int NETWORK_DATA_QUEUE_LEN = 2;
		int m_working_network_data_queue = 0;
		std::queue<NetWorkData> m_network_data_queues[NETWORK_DATA_QUEUE_LEN];
		std::mutex m_network_data_mutex;

		std::thread *m_loop_thread = nullptr;
		bool m_is_runing = false;
		bool m_is_done = false;
		int m_loop_span = 100;

	protected:
		static void CnnEventCb(struct bufferevent *bev, short events, void *ptr);
		static void CnnReadCb(struct bufferevent *bev, void *ctx);
		static void CnnWriteCb(struct bufferevent *bev, void *ctx);
		static void ListenAcceptCb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
		static void ListenErrorCb(struct evconnlistener *listener, void *ctx);
	};
}