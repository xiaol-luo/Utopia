#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"	
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitSight(lua_State *L)
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
                std::string name = "SceneUnitSight";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitSight> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitSight()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitSight"; })				
						,"SetSceneView", &GameLogic::SceneUnitSight::SetSceneView				
						,"SetRadius", &GameLogic::SceneUnitSight::SetRadius				
						,"SetViewCamp", &GameLogic::SceneUnitSight::SetViewCamp				
						,"GetViewCamp", &GameLogic::SceneUnitSight::GetViewCamp				
						,"UpdateState", &GameLogic::SceneUnitSight::UpdateState				
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
						ns_table.set(var_name, GameLogic::SceneUnitSight::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}