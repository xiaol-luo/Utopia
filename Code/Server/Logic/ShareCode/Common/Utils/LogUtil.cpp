#include "LogUtil.h"

LogModule *LogUtil::log_module = nullptr;

bool LogUtil::Init(LogModule *_log_module)
{
	if (nullptr != log_module)
		return false;

	log_module = _log_module;
	return nullptr != log_module;
}