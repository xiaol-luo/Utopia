#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitQTreeNode_EChild(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EChild";
				std::string name_space = "GameLogic.SceneUnitQTreeNode";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EChild_LT", 0,
					"EChild_RT", 1,
					"EChild_RB", 2,
					"EChild_LB", 3,
					"EChild_Count", 4
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}