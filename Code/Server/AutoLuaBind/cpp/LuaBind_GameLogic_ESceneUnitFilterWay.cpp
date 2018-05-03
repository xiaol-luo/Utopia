#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneUnitFilterWay(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ESceneUnitFilterWay";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ESceneUnitFilterWay_ExculdeSuids", 0,
					"ESceneUnitFilterWay_UnitType", 1,
					"ESceneUnitFilterWay_Relation", 2,
					"ESceneUnitFilterWay_ShapeCircle", 3,
					"ESceneUnitFilterWay_ShapeObb2", 4,
					"ESceneUnitFilterWay_ShapeSector", 5,
					"ESceneUnitFilterWay_LimitNum", 6,
					"ESceneUnitFilterWay_Count", 7
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}