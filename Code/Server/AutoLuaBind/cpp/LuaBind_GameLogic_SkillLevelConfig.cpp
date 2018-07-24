#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfig.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfigBase.h"	
#include "CsvConfigSets.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SkillLevelConfig(lua_State *L)
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
                std::string name = "SkillLevelConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SkillLevelConfig> meta_table(
						"__StructName__", sol::property([]() {return "SkillLevelConfig"; })				
						,"skill_cfg", &GameLogic::SkillLevelConfig::skill_cfg				
						,"skill_id", &GameLogic::SkillLevelConfig::skill_id				
						,"level", &GameLogic::SkillLevelConfig::level				
						,"consume_mp", &GameLogic::SkillLevelConfig::consume_mp				
						,"cd", &GameLogic::SkillLevelConfig::cd				
						,"cast_distance", &GameLogic::SkillLevelConfig::cast_distance				
						,"preparing_span", &GameLogic::SkillLevelConfig::preparing_span				
						,"releasing_span", &GameLogic::SkillLevelConfig::releasing_span				
						,"lasting_span", &GameLogic::SkillLevelConfig::lasting_span				
						,"can_move", &GameLogic::SkillLevelConfig::can_move				
						,"release_effect_ids", &GameLogic::SkillLevelConfig::release_effect_ids
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