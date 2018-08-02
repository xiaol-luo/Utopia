#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectScript(lua_State *L)
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
                std::string name = "EffectScript";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectScript> meta_table(
						sol::constructors<				
						GameLogic::EffectScript(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, uint64_t)
						>(),
						"__StructName__", sol::property([]() {return "EffectScript"; })				
						,"SubscribeSuEvent", &GameLogic::EffectScript::SubscribeSuEvent				
						,"RemoveSuEvent", &GameLogic::EffectScript::RemoveSuEvent				
						,"CancelAllSuEvent", &GameLogic::EffectScript::CancelAllSuEvent				
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