#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/skill/CsvSkillLevelConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvSkillLevelConfig(lua_State *L)
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
                std::string name = "CsvSkillLevelConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvSkillLevelConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvSkillLevelConfig"; })				
						,"id", &Config::CsvSkillLevelConfig::id				
						,"level", &Config::CsvSkillLevelConfig::level				
						,"preparing_span", &Config::CsvSkillLevelConfig::preparing_span				
						,"releasing_span", &Config::CsvSkillLevelConfig::releasing_span				
						,"lasting_span", &Config::CsvSkillLevelConfig::lasting_span				
						,"comsume_mp", &Config::CsvSkillLevelConfig::comsume_mp				
						,"cd", &Config::CsvSkillLevelConfig::cd				
						,"cast_distance", &Config::CsvSkillLevelConfig::cast_distance				
						,"can_move", &Config::CsvSkillLevelConfig::can_move				
						,"effect_ids", &Config::CsvSkillLevelConfig::effect_ids				
						,"Init", &Config::CsvSkillLevelConfig::Init
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