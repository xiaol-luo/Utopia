#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitBullet/SceneUnitBullet.h"	
#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitMissile.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitBullet(lua_State *L)
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
                std::string name = "SceneUnitBullet";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitBullet> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitBullet()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitBullet"; })				
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