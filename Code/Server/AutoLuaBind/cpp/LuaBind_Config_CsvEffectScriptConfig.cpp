#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectScriptConfig.h"

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