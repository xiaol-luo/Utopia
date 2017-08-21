#include "NetWorker.h"
#include "event2/event.h"
#include "event2/bufferevent.h"
#include "event2/listener.h"
#include "event2/buffer.h"

namespace Net
{
	NetWorker::NetWorker()
	{

	}

	NetWorker::~NetWorker()
	{

	}

	bool NetWorker::AddCnn(NetId id, int fd, std::weak_ptr<INetworkHandler> handler)
	{
		if (!m_is_runing)
			return false;
		std::shared_ptr<INetworkHandler> sp_handler = handler.lock();
		if (nullptr == sp_handler)
			return false;
		sp_handler->SetNetId(id);

		bool ret = false;
		m_cnn_data_mutex.lock();
		if (m_cnn_datas.count(id) <= 0 && m_wait_add_cnn_datas.count(id) <= 0)
		{
			ret = true;
			NetConnectionData *cnn_data = new NetConnectionData(this, id, fd, handler);
			m_wait_add_cnn_datas[cnn_data->netid] = cnn_data;
		}
		m_cnn_data_mutex.unlock();
		return ret;
	}

	void NetWorker::RemoveCnn(NetId id)
	{
		if (!m_is_runing)
			return;

		m_cnn_data_mutex.lock();
		NetConnectionData *cnn_data = nullptr;
		{
			auto it = m_cnn_datas.find(id);
			if (m_cnn_datas.end() != it)
				cnn_data = it->second;
			if (nullptr == cnn_data)
			{
				it = m_wait_add_cnn_datas.find(id);
				if (m_wait_add_cnn_datas.end() != it)
					cnn_data = it->second;
			}
		}
		if (nullptr != cnn_data)
		{
			if (m_wait_remove_netids.count(id) <= 0 && m_internal_wait_remove_netids.count(id) <= 0)
			{
				NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Close, 0, 0, nullptr, 0);
				this->PushNetworkData(data);
			}
			m_wait_remove_netids.insert(id);
		}
		m_cnn_data_mutex.unlock();
	}

	bool NetWorker::GetNetDatas(std::queue<NetWorkData> *&out_datas)
	{
		out_datas = &m_network_data_queues[m_working_network_data_queue];
		m_network_data_mutex.lock();
		m_working_network_data_queue = (m_working_network_data_queue + 1) % NETWORK_DATA_QUEUE_LEN;
		m_network_data_mutex.unlock();
		return true;
	}

	bool NetWorker::Start()
	{
		if (m_is_done)
			return false;
		if (m_is_runing)
			return true;

		bool ret = false;
		if (nullptr == m_loop_thread)
		{
			ret = true;
			m_is_runing = true;
			m_loop_thread = new std::thread(std::bind(&NetWorker::Loop, this));
		}
		return ret;
	}

	void NetWorker::Stop()
	{
		m_is_done = true;
		m_is_runing = false;
		if (nullptr != m_loop_thread)
		{
			m_loop_thread->join();
			delete m_loop_thread;
			m_loop_thread = nullptr;
		}
	}

	void NetWorker::CnnEventCb(struct bufferevent *bev, short events, void *ctx)
	{
		NetConnectionData *cnn_data = (NetConnectionData *)ctx;
		NetWorker *net_worker = cnn_data->net_worker;
		++net_worker->m_event_cb_times;

		if (events & BEV_EVENT_CONNECTED) 
		{

		}
		else if (events & BEV_EVENT_ERROR) 
		{
			net_worker->m_internal_wait_remove_netids.insert(cnn_data->netid);
			NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Error, -1, 0, nullptr, 0);
			net_worker->PushNetworkData(data);
		}
		else if (events & BEV_EVENT_EOF)
		{
			net_worker->m_internal_wait_remove_netids.insert(cnn_data->netid);
			NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Close, 0, 0, nullptr, 0);
			net_worker->PushNetworkData(data);
		}
	}

	void NetWorker::CnnReadCb(struct bufferevent *bev, void *ctx)
	{
		NetConnectionData *cnn_data = (NetConnectionData *)ctx;
		NetWorker *net_worker = cnn_data->net_worker;
		++net_worker->m_event_cb_times;

		struct evbuffer *in_buffer = bufferevent_get_input(bev);
		size_t len = evbuffer_get_length(in_buffer);
		if (len > 0)
		{
			char *msg = (char *)malloc(len + 1);
			evbuffer_remove(in_buffer, msg, len);
			NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Read, 0, 0, msg, len);
			net_worker->PushNetworkData(data);
		}
	}

	void NetWorker::CnnWriteCb(struct bufferevent *bev, void *ctx)
	{
		NetConnectionData *cnn_data = (NetConnectionData *)ctx;
		NetWorker *net_worker = cnn_data->net_worker;
		++net_worker->m_event_cb_times;
	}

	void NetWorker::ListenAcceptCb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int addresslen, void *ctx)
	{
		NetConnectionData *cnn_data = (NetConnectionData *)ctx;
		NetWorker *net_worker = cnn_data->net_worker;
		++net_worker->m_event_cb_times;

		NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Read, 0, fd, nullptr, 0);
		net_worker->PushNetworkData(data);
	}

	void NetWorker::ListenErrorCb(struct evconnlistener *listener, void *ctx)
	{
		NetConnectionData *cnn_data = (NetConnectionData *)ctx;
		NetWorker *net_worker = cnn_data->net_worker;
		++ net_worker->m_event_cb_times;

		net_worker->m_internal_wait_remove_netids.insert(cnn_data->netid);
		NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Close, 0, 0, nullptr, 0);
		net_worker->PushNetworkData(data);
	}

	void NetWorker::Loop()
	{
		event_base *base = event_base_new();
		while (m_is_runing)
		{
			this->CheckRemoveCnnDatas();
			this->CheckAddCnnDatas(base);

			int loop_times = 0;
			while (loop_times ++ < 1000000)
			{
				int ret = event_base_loop(base, EVLOOP_NONBLOCK);
				if (-1 != ret)
				{
					if (0 == m_event_cb_times)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(m_loop_span));
						break;
					}
					m_event_cb_times = 0;
				}
				else
				{
					int err_num = GetLastError();
					break;
					// do something ?
				}
			}

			this->CheckRemoveCnnDatas();
		} 

		event_base_free(base);
		base = nullptr;
	}

	void NetWorker::PushNetworkData(const NetWorkData &data)
	{
		m_network_data_mutex.lock();
		m_network_data_queues[m_working_network_data_queue].push(data);
		m_network_data_mutex.unlock();
	}

	void NetWorker::CheckAddCnnDatas(event_base *base)
	{
		std::unordered_map<NetId, NetConnectionData *> swap_cnn_datas;
		m_cnn_data_mutex.lock();
		swap_cnn_datas.swap(m_wait_add_cnn_datas);
		m_cnn_data_mutex.unlock();

		if (!swap_cnn_datas.empty())
		{
			for (auto kv_pair : swap_cnn_datas)
			{
				NetId netid = kv_pair.first;
				NetConnectionData *cnn_data = kv_pair.second;

				bool is_ok = true;
				do 
				{
					if (0 != evutil_make_socket_nonblocking(cnn_data->fd))
					{
						cnn_data->fd = -1;
						is_ok = false;
						break;
					}
					if (cnn_data->handler.expired())
					{
						is_ok = false;
						break;
					}

					std::shared_ptr<INetworkHandler> handler = cnn_data->handler.lock();
					if (ENetworkHandler_Connect == handler->HandlerType())
					{
						bufferevent *bev = bufferevent_socket_new(base, cnn_data->fd, BEV_OPT_CLOSE_ON_FREE);
						if (nullptr == bev)
						{
							is_ok = false;
							break;
						}
						bufferevent_setcb(bev, CnnReadCb, CnnWriteCb, CnnEventCb, cnn_data);
						bufferevent_enable(bev, EV_READ);
						// bufferevent_enable(bev, EV_WRITE);
						cnn_data->buffer_ev = bev;
					}
					if (ENetworkHandler_Listen == handler->HandlerType())
					{
						evconnlistener *listener = evconnlistener_new(base, ListenAcceptCb, cnn_data,
							LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 64, cnn_data->fd);
						if (nullptr == listener)
						{
							is_ok = false;
							break;
						}
						evconnlistener_set_error_cb(listener, ListenErrorCb);
						cnn_data->listen_ev = listener;
					}
				} while (false);

				if (is_ok)
				{
					m_cnn_data_mutex.lock();
					m_cnn_datas[netid] = cnn_data;
					m_cnn_data_mutex.unlock();
				}
				else
				{
					NetWorkData data(cnn_data->netid, cnn_data->fd, cnn_data->handler, ENetWorkDataAction_Close, 0, 0, nullptr, 0);
					this->PushNetworkData(data);
					if (cnn_data->fd >= 0)
						evutil_closesocket(cnn_data->fd);
					delete cnn_data;
					continue;
				}
			}
			swap_cnn_datas.clear();
		}
	}

	void NetWorker::CheckRemoveCnnDatas()
	{
		m_cnn_data_mutex.lock();
		m_internal_wait_remove_netids.insert(m_wait_remove_netids.begin(), m_wait_remove_netids.end());
		m_wait_remove_netids.clear();
		if (!m_internal_wait_remove_netids.empty())
		{
			for (NetId netid : m_internal_wait_remove_netids)
			{
				{
					auto it = m_wait_add_cnn_datas.find(netid);
					if (m_wait_add_cnn_datas.end() != it)
					{
						evutil_closesocket(it->second->fd);
						delete it->second;
						m_wait_add_cnn_datas.erase(netid);
					}
				}
				{
					auto it = m_cnn_datas.find(netid);
					if (m_cnn_datas.end() != it)
					{
						evutil_closesocket(it->second->fd);
						if (nullptr != it->second->buffer_ev)
							bufferevent_free(it->second->buffer_ev);
						if (nullptr != it->second->listen_ev)
						evconnlistener_free(it->second->listen_ev);
						delete it->second;
						m_cnn_datas.erase(netid);
					}
				}
			}
			m_internal_wait_remove_netids.clear();
		}
		m_cnn_data_mutex.unlock();
	}
}
