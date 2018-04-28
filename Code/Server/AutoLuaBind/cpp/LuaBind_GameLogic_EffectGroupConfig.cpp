#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "effect/CsvEffectGroupConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectGroup/EffectGroupConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectGroupConfig(lua_State *L)
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
                std::string name = "EffectGroupConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectGroupConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectGroupConfig"; })				
						,"CreateEffect", &GameLogic::EffectGroupConfig::CreateEffect				
						,"InitCfg", &GameLogic::EffectGroupConfig::InitCfg				
						, sol::base_classes, sol::bases<
							GameLogic::EffectConfigBase 
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