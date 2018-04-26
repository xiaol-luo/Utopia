#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectForceMove/EffectForceMove.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectForceMove/EffectForceMoveConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectForceMove(lua_State *L)
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
                std::string name = "EffectForceMove";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectForceMove> meta_table(
						sol::constructors<				
						GameLogic::EffectForceMove(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, unsigned long long)
						>(),
						"__StructName__", sol::property([]() {return "EffectForceMove"; })				
						, sol::base_classes, sol::bases<
							GameLogic::EffectBase 
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