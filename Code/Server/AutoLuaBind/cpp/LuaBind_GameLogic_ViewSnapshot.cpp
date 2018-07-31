#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ViewSnapshot(lua_State *L)
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
                std::string name = "ViewSnapshot";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::ViewSnapshot> meta_table(
						sol::constructors<				
						GameLogic::ViewSnapshot()
						>(),
						"__StructName__", sol::property([]() {return "ViewSnapshot"; })				
						,"view_grids", &GameLogic::ViewSnapshot::view_grids				
						,"scene_units", &GameLogic::ViewSnapshot::scene_units				
						,"Reset", &GameLogic::ViewSnapshot::Reset				
						,"CalDifference", &GameLogic::ViewSnapshot::CalDifference				
						,"CanSeeSu", &GameLogic::ViewSnapshot::CanSeeSu
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