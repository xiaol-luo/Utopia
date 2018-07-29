#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/log/CsvLogConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvLogConfigSet(lua_State *L)
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
                std::string name = "CsvLogConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvLogConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvLogConfigSet"; })				
						,"cfg_check_fun", &Config::CsvLogConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvLogConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvLogConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvLogConfigSet::id_to_key				
						,"Load", &Config::CsvLogConfigSet::Load
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