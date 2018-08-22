#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectScriptConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectScriptConfigSet(lua_State *L)
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
                std::string name = "CsvEffectScriptConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectScriptConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectScriptConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectScriptConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectScriptConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectScriptConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectScriptConfigSet::id_to_key				
						,"Load", &Config::CsvEffectScriptConfigSet::Load
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