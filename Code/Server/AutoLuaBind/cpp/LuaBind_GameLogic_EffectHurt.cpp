#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectHurt/EffectHurt.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectHurt/EffectHurtConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectHurt(lua_State *L)
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
                std::string name = "EffectHurt";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectHurt> meta_table(
						sol::constructors<				
						GameLogic::EffectHurt(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, uint64_t)
						>(),
						"__StructName__", sol::property([]() {return "EffectHurt"; })				
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