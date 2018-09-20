#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/ShareCode/Common/Geometry/Vector2.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ViewGrid(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = GameLogic::EViewCamp;
				using TypeAlias_2 = bool;
				static TypeAlias_2 CanSee1(GameLogic::ViewGrid &cls, TypeAlias_1 p1)
				{
					return cls.CanSee(p1);
				}
				using TypeAlias_3 = int;
				using TypeAlias_4 = bool;
				static TypeAlias_4 CanSee2(GameLogic::ViewGrid &cls, TypeAlias_3 p1)
				{
					return cls.CanSee(p1);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "ViewGrid";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::ViewGrid> meta_table(
						sol::constructors<				
						GameLogic::ViewGrid(int, int, int, Vector2, float, GameLogic::EViewGridType)
						>(),
						"__StructName__", sol::property([]() {return "ViewGrid"; })				
						,"grid_id", &GameLogic::ViewGrid::grid_id				
						,"row", &GameLogic::ViewGrid::row				
						,"col", &GameLogic::ViewGrid::col				
						,"center", &GameLogic::ViewGrid::center				
						,"grid_size", &GameLogic::ViewGrid::grid_size				
						,"grid_type", &GameLogic::ViewGrid::grid_type				
						,"grid_type_group", &GameLogic::ViewGrid::grid_type_group				
						,"observing_num", &GameLogic::ViewGrid::observing_num				
						,"su_bodies", &GameLogic::ViewGrid::su_bodies				
						,"CanSee", sol::overload(ForOverloadFns::CanSee1, ForOverloadFns::CanSee2)
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