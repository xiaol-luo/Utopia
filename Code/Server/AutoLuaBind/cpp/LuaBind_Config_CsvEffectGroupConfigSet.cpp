#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectGroupConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectGroupConfigSet(lua_State *L)
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
                std::string name = "CsvEffectGroupConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectGroupConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectGroupConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectGroupConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectGroupConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectGroupConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectGroupConfigSet::id_to_key				
						,"Load", &Config::CsvEffectGroupConfigSet::Load
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