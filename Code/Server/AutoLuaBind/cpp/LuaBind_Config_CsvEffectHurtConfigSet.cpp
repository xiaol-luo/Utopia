#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Config/AutoCsvCode/effect/CsvEffectHurtConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectHurtConfigSet(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "CsvEffectHurtConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectHurtConfigSet> meta_table(
					"__StructName__", sol::property([]() {return "CsvEffectHurtConfigSet"; })				
						,"cfg_check_fun", &Config::CsvEffectHurtConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvEffectHurtConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvEffectHurtConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvEffectHurtConfigSet::id_to_key				
						,"Load", &Config::CsvEffectHurtConfigSet::Load
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