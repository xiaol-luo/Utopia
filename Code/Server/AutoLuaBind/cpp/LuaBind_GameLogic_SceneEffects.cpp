#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneEffects(lua_State *L)
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
                std::string name = "SceneEffects";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneEffects> meta_table(
						sol::constructors<				
						GameLogic::SceneEffects()
						>(),
						"__StructName__", sol::property([]() {return "SceneEffects"; })				
						,"CreateEffect", &GameLogic::SceneEffects::CreateEffect				
						,"AddEffect", &GameLogic::SceneEffects::AddEffect				
						,"RemoveEffect", &GameLogic::SceneEffects::RemoveEffect				
						, sol::base_classes, sol::bases<
							GameLogic::SceneModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneEffects::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}