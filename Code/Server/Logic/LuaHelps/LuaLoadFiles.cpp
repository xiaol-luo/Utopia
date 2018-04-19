#include "LuaLoadFiles.h"

namespace LuaUtils
{
	bool LoadScripts_LoadSettingFile()
	{
		sol::state_view lsv(LuaUtils::luaState);
		lsv[Load_Files_Table_Name] = nullptr;
		sol::protected_function_result pfr = lsv.script_file(Load_Files_Setting_File, LuaUtils::ErrorFn);
		if (!pfr.valid())
		{
			sol::error e = pfr;
			printf("LoadScripts_LoadSettingFile error: %s \n", e.what());
			return false;
		}
		return true;
	}
	bool LoadScripts_DoLoadScript(bool isReload, std::set<std::string> reloadFilter)
	{
		if (isReload && reloadFilter.empty())
			return true;
		bool loadRet = LoadScripts_LoadSettingFile();
		if (!loadRet)
			return false;

		sol::state_view lsv(LuaUtils::luaState);
		sol::table luaFiles;
		if (isReload)
		{
			luaFiles = lsv.create_table();
			for (std::string tbName : reloadFilter)
			{
				sol::table scriptTb = lsv[tbName];
				if (scriptTb.valid())
					luaFiles.add(scriptTb);
			}
		}
		else
		{
			luaFiles = lsv[Load_Files_Table_Name];
			if (!luaFiles.valid())
			{
				printf("LoadScripts_DoLoadScript error: table %s missing \n", Load_Files_Table_Name);
				return false;
			}
		}
		for (auto item : luaFiles)
		{
			sol::table tb = item.second;
			if (tb.valid())
			{
				for (auto kvPair : tb)
				{
					sol::object ss = kvPair.second;
					std::string filePath = ss.as<std::string>();
					sol::protected_function_result ret = lsv.script_file(filePath, LuaUtils::ErrorFn);
					if (!ret.valid())
					{
						sol::error e = ret;
						printf("LoadScripts_DoLoadScript error: %s \n", e.what());
						loadRet = false;
						break;
					}
					// printf("LoadScripts_DoLoadScript load file %s \n", filePath.c_str());
				}
			}
		}
		return loadRet;
	}

	bool LoadScripts_ReloadEffectScripts()
	{
		std::set<std::string> filter = { Load_Files_Effect_Script_Table_Name };
		return LoadScripts_DoLoadScript(true, filter);
	}
}