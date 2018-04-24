#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"

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
						GameLogic::EffectScript(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, unsigned long long)
						>(),
						"__StructName__", sol::property([]() {return "EffectScript"; })				
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