#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Skills/SkillConfig.h"	
#include "GameLogic/Scene/Skills/SkillConfigBase.h"	
#include "CsvConfigSets.h"

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
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}