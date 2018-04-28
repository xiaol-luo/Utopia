#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "effect/CsvEffectSearcherConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectSearcherConfig(lua_State *L)
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
                std::string name = "CsvEffectSearcherConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectSearcherConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectSearcherConfig"; })				
						,"id", &Config::CsvEffectSearcherConfig::id				
						,"filter_id", &Config::CsvEffectSearcherConfig::filter_id				
						,"effect_ids", &Config::CsvEffectSearcherConfig::effect_ids				
						,"Init", &Config::CsvEffectSearcherConfig::Init
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