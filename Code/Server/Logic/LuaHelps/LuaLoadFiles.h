#pragma once
#include <sol.hpp>
#include "Utils/LuaUtils.h"
#include <string>
#include <set>


namespace LuaUtils
{
	const static char * Load_Files_Table_Name = "_load_files_map";
	const static char * Load_Files_Effect_Script_Table_Name = "_load_files_effect_script";
	const static char * Load_Files_Setting_File = "LuaScript/setting_loadfiles.lua";

	extern bool LoadScripts_LoadSettingFile();
	extern bool LoadScripts_DoLoadScript(bool isReload, std::set<std::string> reloadFilter);
	extern bool LoadScripts_ReloadEffectScripts();
}
