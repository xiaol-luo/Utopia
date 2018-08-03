#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "effect/CsvEffectScriptConfig.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectScriptConfig(lua_State *L)
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
                std::string name = "EffectScriptConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectScriptConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectScriptConfig"; })				
						,"CreateEffect", &GameLogic::EffectScriptConfig::CreateEffect				
						,"InitCfg", &GameLogic::EffectScriptConfig::InitCfg				
						,"GetClassName", &GameLogic::EffectScriptConfig::GetClassName				
						,"GetStrParam", &GameLogic::EffectScriptConfig::GetStrParam				
						,"GetJsonParam", &GameLogic::EffectScriptConfig::GetJsonParam				
						,"GetIntParam", &GameLogic::EffectScriptConfig::GetIntParam				
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