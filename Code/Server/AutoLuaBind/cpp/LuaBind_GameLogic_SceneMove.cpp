#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/Navigation/NavMesh.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "GameLogic/Scene/SceneModule/SceneMove/SceneMove.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneMove(lua_State *L)
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
                std::string name = "SceneMove";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneMove> meta_table(
						sol::constructors<				
						GameLogic::SceneMove()
						>(),
						"__StructName__", sol::property([]() {return "SceneMove"; })				
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
						ns_table.set(var_name, GameLogic::SceneMove::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}