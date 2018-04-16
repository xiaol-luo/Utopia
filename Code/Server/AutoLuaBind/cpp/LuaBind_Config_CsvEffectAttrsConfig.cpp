#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectAttrsConfig(lua_State *L)
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
                std::string name = "CsvEffectAttrsConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectAttrsConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectAttrsConfig"; })				
						,"id", &Config::CsvEffectAttrsConfig::id				
						,"base_attrs", &Config::CsvEffectAttrsConfig::base_attrs				
						,"extra_attrs", &Config::CsvEffectAttrsConfig::extra_attrs				
						,"percent_attrs", &Config::CsvEffectAttrsConfig::percent_attrs				
						,"hold_time_ms", &Config::CsvEffectAttrsConfig::hold_time_ms				
						,"unique_id", &Config::CsvEffectAttrsConfig::unique_id				
						,"Init", &Config::CsvEffectAttrsConfig::Init
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