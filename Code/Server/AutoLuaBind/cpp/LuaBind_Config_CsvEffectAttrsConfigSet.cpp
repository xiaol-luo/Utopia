#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectAttrsConfigSet(lua_State *L)
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
                std::string name = "CsvEffectAttrsConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectAttrsConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectAttrsConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectAttrsConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectAttrsConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectAttrsConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectAttrsConfigSet::id_to_key				
						,"Load", &Config::CsvEffectAttrsConfigSet::Load
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