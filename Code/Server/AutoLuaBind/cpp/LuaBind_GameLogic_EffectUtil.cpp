#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectUtils.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectUtil(lua_State *L)
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
                std::string name = "EffectUtil";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectUtil> meta_table(
						"__StructName__", sol::property([]() {return "EffectUtil"; })				
						,"UnitCanBeHurt", &GameLogic::EffectUtil::UnitCanBeHurt				
						,"UnitIsAlive", &GameLogic::EffectUtil::UnitIsAlive
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