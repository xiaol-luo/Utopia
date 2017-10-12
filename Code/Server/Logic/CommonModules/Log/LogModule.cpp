#include "LogModule.h"
#include "ModuleDef/ModuleMgr.h"
#include "log/CsvLogConfig.h"

enum ELoggerType
{
	ELoggerType_Invalid = 0,
	ELoggerType_Stdout,
	ELoggerType_Stderr,
	ELoggerType_Common,
	ELoggerType_Rotating,
	ELoggerType_Daily,
	ELoggerType_Max,
};

LogModule::LogModule(ModuleMgr *module_mgr) : ILogModule(module_mgr)
{

}

LogModule::~LogModule() 
{

}

void LogModule::Record(ELogLevel log_level, int log_id, std::string msg)
{
	Log(log_level, log_id, msg.c_str());
}

void LogModule::Record(ELogLevel log_level, int log_id, const char *msg)
{
	Log(log_level, log_id, msg);
}

EModuleRetCode LogModule::Init(void *param)
{
	bool ret = true;
	do 
	{
		spdlog::set_async_mode(m_async_queue_size);
		spdlog::set_level(spdlog::level::debug);

		Config::CsvLogConfigSet cfg_set;
		std::string *file_path = (std::string *)param;
		ret = cfg_set.Load(*file_path);
		if (!ret || cfg_set.cfg_vec.size() < 2)
		{
			ret = false;
			break;
		}
		
		std::map<int, Config::CsvLogConfig *> cfg_map = cfg_set.id_to_key;
		int max_log_id = -1;
		for (auto kv_pair : cfg_map)
		{
			int logger_id = kv_pair.first;
			if (logger_id > max_log_id)
				max_log_id = logger_id;
		}
		if (max_log_id < LOGGER_ID_STDOUT)
		{
			ret = false;
			break;
		}

		m_logger_num = max_log_id + 1;
		m_log_datas = new LogData[m_logger_num];
		m_loggers = new std::shared_ptr<spdlog::logger>[m_logger_num];
		/*
		{
			m_loggers[LOGGER_ID_STDERR] = spdlog::stderr_color_mt(stderr_cfg->name);
			m_loggers[LOGGER_ID_STDERR]->set_level((spdlog::level::level_enum)stderr_cfg->log_level);
			m_log_datas[LOGGER_ID_STDERR].log_level = (ELogLevel)stderr_cfg->log_level;
		}
		{
			m_loggers[LOGGER_ID_STDOUT] = spdlog::stderr_color_mt(stdout_cfg->name);
			m_loggers[LOGGER_ID_STDOUT]->set_level((spdlog::level::level_enum)stdout_cfg->log_level);
			m_log_datas[LOGGER_ID_STDOUT].log_level = (ELogLevel)stdout_cfg->log_level;
		}
		*/

		for (auto kv_pair : cfg_map)
		{
			int logger_id = kv_pair.first;
			Config::CsvLogConfig *cfg = kv_pair.second;

			std::shared_ptr<spdlog::logger> logger = nullptr;
			switch (cfg->logger_type)
			{
			case ELoggerType_Stderr:
			{
				logger = spdlog::stderr_color_mt(cfg->name);
			}
			break;
			case ELoggerType_Stdout:
			{
				logger = spdlog::stdout_color_mt(cfg->name);
			}
			break;
			case ELoggerType_Common:
			{
				logger = spdlog::basic_logger_mt(cfg->name, cfg->save_file, false);
			}
			break;
			case ELoggerType_Rotating:
			{
				logger = spdlog::rotating_logger_mt(cfg->name,
					cfg->save_file, cfg->rorating_max_size, cfg->rorating_max_files);
			}
			break;
			case ELoggerType_Daily:
			{
				logger = spdlog::daily_logger_mt(cfg->name,
					cfg->save_file, cfg->daily_hour, cfg->daily_min);
			}
			break;
			}
			if (nullptr == logger)
			{
				ret = false;
				break;
			}
			logger->set_level((spdlog::level::level_enum)cfg->log_level);
			m_loggers[logger_id] = logger;
			LogData &log_data = m_log_datas[logger_id];
			log_data.log_id = logger_id;
			log_data.log_level = (ELogLevel)cfg->log_level;
			log_data.write_loggers.insert(logger);
		}

		for (int curr_log_id = LOGGER_ID_STDOUT; curr_log_id < m_logger_num; ++curr_log_id)
		{
			std::shared_ptr<spdlog::logger> curr_logger = m_loggers[curr_log_id];
			if (nullptr == curr_logger)
				continue;

			auto curr_cfg_it = cfg_map.find(curr_log_id);
			if (cfg_map.end() != curr_cfg_it)
			{
				Config::CsvLogConfig *curr_log_cfg = curr_cfg_it->second;
				std::set<int> related_log_ids(curr_log_cfg->alsoWritetoMe.begin(), curr_log_cfg->alsoWritetoMe.end());
				for (int log_id = LOGGER_ID_STDERR + 1; log_id <= max_log_id; ++log_id)
				{
					if (log_id == curr_log_id)
						continue;
					if (nullptr == m_loggers[log_id])
						continue;
					if (related_log_ids.count(-1) <= 0 && related_log_ids.count(log_id) <= 0)
						continue;
					m_log_datas[log_id].write_loggers.insert(curr_logger);
				}
			}
		}
	} while (false);

	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
}

EModuleRetCode LogModule::Awake()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Update()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Destroy()
{
	delete[]m_log_datas; m_log_datas = nullptr;
	for (int i = 0; i < m_logger_num; ++i)
	{
		m_loggers[i] = nullptr;
	}
	m_logger_num = 0;
	delete[]m_loggers; m_loggers = nullptr;
	spdlog::drop_all();
	return EModuleRetCode_Succ;
}
