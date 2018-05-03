#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectForceMoveConfig.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectForceMove/EffectForceMoveConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectForceMoveConfig(lua_State *L)
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
                std::string name = "EffectForceMoveConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectForceMoveConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectForceMoveConfig"; })				
						,"CreateEffect", &GameLogic::EffectForceMoveConfig::CreateEffect				
						,"GetTimeSec", &GameLogic::EffectForceMoveConfig::GetTimeSec				
						,"GetSpeed", &GameLogic::EffectForceMoveConfig::GetSpeed				
						,"IgnoreTerrian", &GameLogic::EffectForceMoveConfig::IgnoreTerrian				
						,"GetMoveDeg", &GameLogic::EffectForceMoveConfig::GetMoveDeg				
						,"GetAnchor", &GameLogic::EffectForceMoveConfig::GetAnchor				
						,"InitCfg", &GameLogic::EffectForceMoveConfig::InitCfg				
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