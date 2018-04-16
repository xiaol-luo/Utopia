#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Utils/NumUtils.h"

namespace SolLuaBind
{
	void LuaBind_NumUtil_ECalculateStrategy(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ECalculateStrategy";
				std::string name_space = "NumUtil";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ECS_Overlay", 0,
					"ECS_MaxPriority", 1,
					"ECS_MinPriority", 2,
					"ECS_Count", 3
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}