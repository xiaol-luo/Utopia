#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectFilterConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Config/SceneAllConfig.h"	
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectConfigMgr.h"	
#include "Logic/LogicModules/GameLogic/Scene/Skills/SkillConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneAllConfig(lua_State *L)
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
                std::string name = "SceneAllConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneAllConfig> meta_table(
						sol::constructors<				
						GameLogic::SceneAllConfig()
						>(),
						"__StructName__", sol::property([]() {return "SceneAllConfig"; })				
						,"scene_cfg", &GameLogic::SceneAllConfig::scene_cfg				
						,"effect_filter_cfg_mgr", &GameLogic::SceneAllConfig::effect_filter_cfg_mgr				
						,"skill_cfgs", &GameLogic::SceneAllConfig::skill_cfgs				
						,"effect_cfg_mgr", &GameLogic::SceneAllConfig::effect_cfg_mgr
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