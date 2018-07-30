#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "effect/CsvEffectHurtConfig.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectHurt/EffectHurtConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectHurtConfig(lua_State *L)
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
                std::string name = "EffectHurtConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectHurtConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectHurtConfig"; })				
						,"CreateEffect", &GameLogic::EffectHurtConfig::CreateEffect				
						,"InitCfg", &GameLogic::EffectHurtConfig::InitCfg				
						,"GetHurt", &GameLogic::EffectHurtConfig::GetHurt				
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