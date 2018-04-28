#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavMesh.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneNavMesh(lua_State *L)
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
                std::string name = "SceneNavMesh";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneNavMesh> meta_table(
						sol::constructors<				
						GameLogic::SceneNavMesh()
						>(),
						"__StructName__", sol::property([]() {return "SceneNavMesh"; })				
						,"GetNavMesh", &GameLogic::SceneNavMesh::GetNavMesh				
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
						ns_table.set(var_name, GameLogic::SceneNavMesh::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}