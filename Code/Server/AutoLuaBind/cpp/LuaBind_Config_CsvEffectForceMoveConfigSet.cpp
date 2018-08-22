#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectForceMoveConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectForceMoveConfigSet(lua_State *L)
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
                std::string name = "CsvEffectForceMoveConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectForceMoveConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectForceMoveConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectForceMoveConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectForceMoveConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectForceMoveConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectForceMoveConfigSet::id_to_key				
						,"Load", &Config::CsvEffectForceMoveConfigSet::Load
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