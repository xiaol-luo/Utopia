#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Config/AutoCsvCode/skill/CsvSkillLevelConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvSkillLevelConfigSet(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "CsvSkillLevelConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvSkillLevelConfigSet> meta_table(
					"__StructName__", sol::property([]() {return "CsvSkillLevelConfigSet"; })				
						,"cfg_check_fun", &Config::CsvSkillLevelConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvSkillLevelConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvSkillLevelConfigSet::cfg_vec				
						,"id_to_group", &Config::CsvSkillLevelConfigSet::id_to_group				
						,"Load", &Config::CsvSkillLevelConfigSet::Load
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