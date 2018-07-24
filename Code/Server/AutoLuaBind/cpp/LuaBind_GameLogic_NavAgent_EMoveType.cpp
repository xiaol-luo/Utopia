#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Navigation/NavAgent.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_NavAgent_EMoveType(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EMoveType";
				std::string name_space = "GameLogic.NavAgent";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EMoveType_None", 0,
					"EMoveType_MovePos", 1,
					"EMoveType_MoveDir", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}