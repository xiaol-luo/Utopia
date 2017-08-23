#pragma once

#include <string>
#include <functional>
#include "Common/Define/NetworkDefine.h"

namespace Net
{
	enum EConnectTaskType
	{
		EConnectTask_Connect,
		EConnectTask_Listen,
		EConnectTaskType_Max,
	};

	enum EConnectTaskState
	{
		EConnectTask_Ready,
		EConnectTask_Process,
		EConnectTask_Done,
		EConnectTaskState_Max,
	};

	struct ConnectResult
	{
		EConnectTaskType task_type = EConnectTaskType_Max;
		int err_num = 0;
		std::string err_msg;
		long long id = 0;
		int fd = -1;
	};

	class ConnectTask
	{
	public:
		ConnectTask(EConnectTaskType task_type, int64_t id);
		virtual ~ConnectTask();
		virtual void Process() = 0;
		EConnectTaskType TaskType() { return m_task_type; }
		EConnectTaskState TaskState() { return m_task_state; }
		int64_t Id() { return m_id; }
		const ConnectResult & GetResult() { return m_result; }

	protected:
		EConnectTaskType m_task_type = EConnectTaskType_Max;
		EConnectTaskState m_task_state = EConnectTask_Ready;
		int64_t m_id = 0;
		ConnectResult m_result;
	};

	class ConnectTaskConnect : public ConnectTask
	{
	public:
		ConnectTaskConnect(int64_t id, std::string ip, uint16_t port, void *opt);
		virtual ~ConnectTaskConnect();
		virtual void Process();

	protected:
		std::string m_ip;
		uint16_t m_port = 0;
		void *m_opt = nullptr;
	};

	class ConnectTaskListen : public ConnectTask
	{
	public:
		ConnectTaskListen(int64_t id, std::string ip, uint16_t port, void *opt);
		virtual ~ConnectTaskListen();
		virtual void Process();

	protected:
		std::string m_ip;
		uint16_t m_port = 0;
		void *m_opt = nullptr;
	};
}