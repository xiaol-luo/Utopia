#include "NetWorker.h"

namespace Net
{
	NetWorker::NetWorker()
	{

	}

	NetWorker::~NetWorker()
	{

	}

	bool NetWorker::AddCnn(NetId id, int fd, std::weak_ptr<NetworkHandler> handler)
	{
		bool ret = false;
		m_cnn_data_mutex.lock();
		if (m_cnn_datas.count(id) <= 0 && m_wait_add_cnn_datas.count(id) <= 0)
		{
			ret = true;
			NetConnectionData *cnn_data = new NetConnectionData(id, fd, handler);
			m_wait_add_cnn_datas[cnn_data->netid] = cnn_data;
		}
		m_cnn_data_mutex.unlock();
		return ret;
	}

	void NetWorker::RemoveCnn(NetId id)
	{
		m_cnn_data_mutex.lock();
		if (m_cnn_datas.count(id) >= 0 || m_wait_add_cnn_datas.count(id) >= 0)
		{
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
		return true;
	}

	void NetWorker::Stop()
	{

	}
}
