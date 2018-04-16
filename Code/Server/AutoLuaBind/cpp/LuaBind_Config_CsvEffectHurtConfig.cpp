#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectHurtConfig(lua_State *L)
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
                std::string name = "CsvEffectHurtConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectHurtConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectHurtConfig"; })				
						,"id", &Config::CsvEffectHurtConfig::id				
						,"value", &Config::CsvEffectHurtConfig::value				
						,"filter_id", &Config::CsvEffectHurtConfig::filter_id				
						,"Init", &Config::CsvEffectHurtConfig::Init
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