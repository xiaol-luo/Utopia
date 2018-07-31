#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfigBase.h"	
#include "Config/AutoCsvCode/CsvConfigSets.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SkillConfig(lua_State *L)
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
                std::string name = "SkillConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SkillConfig> meta_table(
						"__StructName__", sol::property([]() {return "SkillConfig"; })				
						,"is_normal_attack", &GameLogic::SkillConfig::is_normal_attack				
						,"use_way", &GameLogic::SkillConfig::use_way				
						,"target_relations", &GameLogic::SkillConfig::target_relations				
						,"target_types", &GameLogic::SkillConfig::target_types				
						,"max_level", &GameLogic::SkillConfig::max_level				
						,"level_cfgs", &GameLogic::SkillConfig::level_cfgs				
						,"GetLvlCfg", &GameLogic::SkillConfig::GetLvlCfg				
						, sol::base_classes, sol::bases<
							GameLogic::SkillConfigBase 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MAX_SKILL_LEVEL";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::MAX_SKILL_LEVEL);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}