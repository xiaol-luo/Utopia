#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectFilterConfigSet(lua_State *L)
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
                std::string name = "CsvEffectFilterConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectFilterConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectFilterConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectFilterConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectFilterConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectFilterConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectFilterConfigSet::id_to_key				
						,"Load", &Config::CsvEffectFilterConfigSet::Load
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