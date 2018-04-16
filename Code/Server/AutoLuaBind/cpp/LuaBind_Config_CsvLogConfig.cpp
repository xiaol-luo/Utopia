#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Config/AutoCsvCode/log/CsvLogConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvLogConfig(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "CsvLogConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvLogConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvLogConfig"; })				
						,"id", &Config::CsvLogConfig::id				
						,"alsoWritetoMe", &Config::CsvLogConfig::alsoWritetoMe				
						,"logger_type", &Config::CsvLogConfig::logger_type				
						,"name", &Config::CsvLogConfig::name				
						,"log_level", &Config::CsvLogConfig::log_level				
						,"save_file", &Config::CsvLogConfig::save_file				
						,"rorating_max_size", &Config::CsvLogConfig::rorating_max_size				
						,"rorating_max_files", &Config::CsvLogConfig::rorating_max_files				
						,"daily_hour", &Config::CsvLogConfig::daily_hour				
						,"daily_min", &Config::CsvLogConfig::daily_min				
						,"Init", &Config::CsvLogConfig::Init
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}