#include "Log.h"

std::shared_ptr<spdlog::logger> g_SpdLogConsole = nullptr;

void ConsoleLogInit(spdlog::level::level_enum logLevel)
{
	g_SpdLogConsole = spdlog::stdout_color_mt("console");
	g_SpdLogConsole->set_level(logLevel);
}

void ConsoleLogUninit()
{
	g_SpdLogConsole = nullptr;
}

Log & Log::Instance()
{
	static Log log;
	return log;
}

Log::Log()
{

}

Log::~Log()
{

}

bool Log::Init()
{
	spdlog::set_async_mode(1024 * 64);
	spdlog::set_level(spdlog::level::debug);

	m_loggers[LogConsole] = spdlog::stdout_color_mt("Console");
	// m_loggers[LogFile] = spdlog::basic_logger_mt("File", "file.log");
	// m_loggers[LogRotate] = spdlog::rotating_logger_mt("Rotate", "rotate/rotate.log", 1024, 1024);
	// m_loggers[LogDaily] = spdlog::daily_logger_mt("Daily", "daily/daily.log", 0, 5);

	return true;
}

void Log::Uninit()
{
	for (int i = 0; i < LogCount; ++i)
	{
		m_loggers[i] = nullptr;
	}

	spdlog::drop_all();
}

