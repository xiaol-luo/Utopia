#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Defines/ViewDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EViewGridType(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EViewGridType";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EViewGrid_Ground", 0,
					"EViewGrid_Wall", 1,
					"EViewGrid_Grass", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}