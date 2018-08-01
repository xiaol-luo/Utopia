#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Config/AutoCsvCode/effect/CsvEffectHealConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectHealConfig(lua_State *L)
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
                std::string name = "CsvEffectHealConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectHealConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectHealConfig"; })				
						,"id", &Config::CsvEffectHealConfig::id				
						,"value", &Config::CsvEffectHealConfig::value				
						,"Init", &Config::CsvEffectHealConfig::Init
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