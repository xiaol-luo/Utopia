#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"	
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ViewSnapshotDifference(lua_State *L)
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
                std::string name = "ViewSnapshotDifference";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::ViewSnapshotDifference> meta_table(
						sol::constructors<				
						GameLogic::ViewSnapshotDifference()
						>(),
						"__StructName__", sol::property([]() {return "ViewSnapshotDifference"; })				
						,"miss_su", &GameLogic::ViewSnapshotDifference::miss_su				
						,"more_su", &GameLogic::ViewSnapshotDifference::more_su				
						,"miss_view_grids", &GameLogic::ViewSnapshotDifference::miss_view_grids				
						,"more_view_grids", &GameLogic::ViewSnapshotDifference::more_view_grids				
						,"Reset", &GameLogic::ViewSnapshotDifference::Reset				
						,"PrintLog", &GameLogic::ViewSnapshotDifference::PrintLog
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