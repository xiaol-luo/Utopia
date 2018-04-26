#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/skill/CsvSkillConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvSkillConfig(lua_State *L)
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
                std::string name = "CsvSkillConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvSkillConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvSkillConfig"; })				
						,"id", &Config::CsvSkillConfig::id				
						,"name", &Config::CsvSkillConfig::name				
						,"is_normal_attack", &Config::CsvSkillConfig::is_normal_attack				
						,"use_way", &Config::CsvSkillConfig::use_way				
						,"target_relations", &Config::CsvSkillConfig::target_relations				
						,"target_types", &Config::CsvSkillConfig::target_types				
						,"Init", &Config::CsvSkillConfig::Init
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