#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectHealConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectHealConfigSet(lua_State *L)
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
                std::string name = "CsvEffectHealConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectHealConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectHealConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectHealConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectHealConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectHealConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectHealConfigSet::id_to_key				
						,"Load", &Config::CsvEffectHealConfigSet::Load
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