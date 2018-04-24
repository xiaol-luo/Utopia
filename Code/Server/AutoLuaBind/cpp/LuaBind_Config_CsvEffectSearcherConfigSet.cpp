#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "effect/CsvEffectSearcherConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectSearcherConfigSet(lua_State *L)
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
                std::string name = "CsvEffectSearcherConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectSearcherConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectSearcherConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectSearcherConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectSearcherConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectSearcherConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectSearcherConfigSet::id_to_key				
						,"Load", &Config::CsvEffectSearcherConfigSet::Load
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