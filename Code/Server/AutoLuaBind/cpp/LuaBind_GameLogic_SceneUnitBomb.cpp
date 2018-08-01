#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Missile/SceneUnitBomb/SceneUnitBomb.h"	
#include "LogicModules/GameLogic/Scene/Missile/SceneUnitMissile.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitBomb(lua_State *L)
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
                std::string name = "SceneUnitBomb";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitBomb> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitBomb()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitBomb"; })				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitMissile 
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