#include "UserType/TryUserTypeUtil.h"
#include <sol.hpp>
#include "AutoBind/AutoHead.h"

namespace TryUserType
{
	void LuaBind_TryEnum(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L /*, const std::string &name_space, const std::string &name*/)
			{
				std::string name = "TryEnum";
				std::string name_space = "";

				sol::state_view lua(L);
				sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"E1", 0,
					"E2", 3,
					"E3", 4,
					"E4", 5
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}
