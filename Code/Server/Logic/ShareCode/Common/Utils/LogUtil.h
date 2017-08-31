#pragma once

#include "CommonModules\Log\LogModule.h"

class LogUtil
{
public:
	static bool Init(LogModule *_log_module);
	static void Destroy() { log_module = nullptr; }

public:
	template <typename... Args>
	static void Debug(int log_id, const char* fmt, const Args&... args)
	{
		log_module->Log(ELogLevel_Debug, log_id, fmt, args...);
	}

	template <typename... Args>
	static void Info(int log_id, const char* fmt, const Args&... args)
	{
		log_module->Log(ELogLevel_Info, log_id, fmt, args...);
	}

	template <typename... Args>
	static void Warn(int log_id, const char* fmt, const Args&... args)
	{
		if (log_id >= 0 && log_id < m_logger_num)
		{
			log_module->Log(ELogLevel_Warn, log_id, fmt, args...);
		}
	}

	template <typename... Args>
	static void Error(int log_id, const char* fmt, const Args&... args)
	{
		log_module->Log(ELogLevel_Err, log_id, fmt, args...);
	}

	template <typename... Args>
	static void Log(ELogLevel log_level, int log_id, const char* fmt, const Args&... args)
	{
		log_module->Log(log_level, log_id, fmt, Args...);
	}

private:
	static LogModule *log_module;
};