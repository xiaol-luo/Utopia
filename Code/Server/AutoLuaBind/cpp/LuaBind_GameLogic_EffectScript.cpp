#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

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
						,"GetSu", &GameLogic::EffectScript::GetSu				
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