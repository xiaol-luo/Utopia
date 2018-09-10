#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "effect/CsvEffectScriptConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectScriptConfig(lua_State *L)
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
                std::string name = "CsvEffectScriptConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectScriptConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectScriptConfig"; })				
						,"id", &Config::CsvEffectScriptConfig::id				
						,"class_name", &Config::CsvEffectScriptConfig::class_name				
						,"str_param", &Config::CsvEffectScriptConfig::str_param				
						,"json_param", &Config::CsvEffectScriptConfig::json_param				
						,"int_param", &Config::CsvEffectScriptConfig::int_param				
						,"Init", &Config::CsvEffectScriptConfig::Init
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