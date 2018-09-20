#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LuaHelps/LuaLoadFiles.h"

namespace SolLuaBind
{
	void LuaBind_LuaUtils(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "LuaUtils";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "Load_Files_Setting_File";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, LuaUtils::Load_Files_Setting_File);
				}				
				{
					std::string name = "Load_Files_Table_Name";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, LuaUtils::Load_Files_Table_Name);
				}				
				{
					std::string name = "LoadScripts_LoadSettingFile";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, LuaUtils::LoadScripts_LoadSettingFile);
				}				
				{
					std::string name = "LoadScripts_DoLoadScript";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, LuaUtils::LoadScripts_DoLoadScript);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}