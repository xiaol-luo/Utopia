#pragma once

#include "ILogModule.h"
#include <set>

class LogModule : public ILogModule
{
public:
	LogModule(ModuleMgr *module_mgr);
	virtual ~LogModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();

	virtual void Record(ELogLevel log_level, int log_id, std::string msg);
	virtual void Record(ELogLevel log_level, int log_id, const char *msg);

public:
	template <typename... Args>
	void Debug(int log_id, const char* fmt, const Args&... args)
	{
		this->Log(ELogLevel_Debug, log_id, fmt, args...);
	}

	template <typename... Args>
	void Info(int log_id, const char* fmt, const Args&... args)
	{
		this->Log(ELogLevel_Info, log_id, fmt, args...);
	}

	template <typename... Args>
	void Warn(int log_id, const char* fmt, const Args&... args)
	{
		if (log_id >= 0 && log_id < m_logger_num)
		{
			this->Log(ELogLevel_Warn, log_id, fmt, args...);
		}
	}

	template <typename... Args>
	void Error(int log_id, const char* fmt, const Args&... args)
	{
		this->Log(ELogLevel_Err, log_id, fmt, args...);
	}

	template <typename... Args>
	void Log(ELogLevel log_level, int log_id, const char* fmt, const Args&... args)
	{
		if (log_id >= 0 && log_id < m_logger_num)
		{
			LogData &data = m_log_datas[log_id];
			if (!data.write_loggers.empty() && log_level >= data.log_level)
			{
				for (auto logger : data.write_loggers)
				{
					logger->log((spdlog::level::level_enum)log_level, fmt, args...);
				}
			}

			if (log_level >= ELogLevel_Err)
			{
				m_loggers[LOGGER_ID_STDERR]->log((spdlog::level::level_enum)log_level, fmt, args...);
			}
		}
	}

protected:
	static const int LOGGER_ID_STDERR = 2;
	static const int LOGGER_ID_STDOUT = 1;
	int m_logger_num = 0;
	std::shared_ptr<spdlog::logger> *m_loggers = nullptr;

	struct LogData
	{
		int log_id = -1;
		ELogLevel log_level = ELogLevel_Invalid;
		std::set<std::shared_ptr<spdlog::logger>> write_loggers;
	};

	LogData *m_log_datas = nullptr;
	int m_async_queue_size =  1024 * 16;

private:

};