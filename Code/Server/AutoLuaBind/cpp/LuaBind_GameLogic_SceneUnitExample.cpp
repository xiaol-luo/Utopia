#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitExample.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitExample(lua_State *L)
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
                std::string name = "SceneUnitExample";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitExample> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitExample()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitExample"; })				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitModule 
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
						ns_table.set(var_name, GameLogic::SceneUnitExample::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}