#ifndef __LOG_H__
#define __LOG_H__

#include "spdlog/spdlog.h"

extern std::shared_ptr<spdlog::logger> g_SpdLogConsole;
void ConsoleLogInit(spdlog::level::level_enum logLevel);
void ConsoleLogUninit();

#define LogInit			Log::Instance().Init
#define LogUninit		Log::Instance().Uninit
#define LogDebug		Log::Instance().Debug
#define LogInfo			Log::Instance().Info
#define LogWarn			Log::Instance().Warn
#define LogError		Log::Instance().Error

enum LogType
{
	LogConsole = 0,
	// LogFile,
	//LogRotate,
	//LogDaily,

	LogCount,
};

class Log
{
public:
	static Log & Instance();

	Log();
	~Log();

	bool Init();
	void Uninit();

	template <typename... Args>
	void Debug(int logType, const char* fmt, const Args&... args)
	{
		if (logType < 0 || logType > LogCount)
			return;

		m_loggers[logType]->debug(fmt, args...);
	}

	template <typename... Args>
	void Info(int logType, const char* fmt, const Args&... args)
	{
		m_loggers[logType]->info(fmt, args...);
	}

	template <typename... Args>
	void Warn(int logType, const char* fmt, const Args&... args)
	{
		m_loggers[logType]->warn(fmt, args...);
	}

	template <typename... Args>
	void Error(int logType, const char* fmt, const Args&... args)
	{
		m_loggers[logType]->error(fmt, args...);
	}

	std::shared_ptr<spdlog::logger> m_loggers[LogCount];
};

#endif
