#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/SceneView.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"	
#include "ShareCode/Network/Protobuf/Battle.pb.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneView(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = float;
				using TypeAlias_2 = float;
				using TypeAlias_3 = GameLogic::ViewGrid *;
				static TypeAlias_3 GetGrid1(GameLogic::SceneView &cls, TypeAlias_1 p1, TypeAlias_2 p2)
				{
					return cls.GetGrid(p1, p2);
				}
				using TypeAlias_4 = int;
				using TypeAlias_5 = GameLogic::ViewGrid *;
				static TypeAlias_5 GetGrid2(GameLogic::SceneView &cls, TypeAlias_4 p1)
				{
					return cls.GetGrid(p1);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SceneView";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneView> meta_table(
						sol::constructors<				
						GameLogic::SceneView()
						>(),
						"__StructName__", sol::property([]() {return "SceneView"; })				
						,"GetCircleCoverGrids", &GameLogic::SceneView::GetCircleCoverGrids				
						,"GetAABBConverGrids", &GameLogic::SceneView::GetAABBConverGrids				
						,"CalGridIdx", &GameLogic::SceneView::CalGridIdx				
						,"CalRowCol", &GameLogic::SceneView::CalRowCol				
						,"InRowIdx", &GameLogic::SceneView::InRowIdx				
						,"InColIdx", &GameLogic::SceneView::InColIdx				
						,"InGridIdx", &GameLogic::SceneView::InGridIdx				
						,"GetUpGrid", &GameLogic::SceneView::GetUpGrid				
						,"GetRightGrid", &GameLogic::SceneView::GetRightGrid				
						,"GetButtomGrid", &GameLogic::SceneView::GetButtomGrid				
						,"GetLeftGrid", &GameLogic::SceneView::GetLeftGrid				
						,"GetSnapshot", &GameLogic::SceneView::GetSnapshot				
						,"GetPreSnapshot", &GameLogic::SceneView::GetPreSnapshot				
						,"MakeSnapshot", &GameLogic::SceneView::MakeSnapshot				
						,"FillPbViewSnapshot", &GameLogic::SceneView::FillPbViewSnapshot				
						,"FillPbViewAllGrids", &GameLogic::SceneView::FillPbViewAllGrids				
						,"GetGrid", sol::overload(ForOverloadFns::GetGrid1, ForOverloadFns::GetGrid2)				
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
						ns_table.set(var_name, GameLogic::SceneView::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}