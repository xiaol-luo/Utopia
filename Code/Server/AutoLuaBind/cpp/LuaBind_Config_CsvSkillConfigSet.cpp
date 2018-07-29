#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/skill/CsvSkillConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvSkillConfigSet(lua_State *L)
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
                std::string name = "CsvSkillConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvSkillConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvSkillConfigSet"; })				
						,"cfg_check_fun", &Config::CsvSkillConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvSkillConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvSkillConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvSkillConfigSet::id_to_key				
						,"Load", &Config::CsvSkillConfigSet::Load
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