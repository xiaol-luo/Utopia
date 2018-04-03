#include "UserType/TryUserTypeUtil.h"
#include <sol.hpp>
#include "AutoBind/AutoHead.h"

namespace TryUserType
{
	void LuaBind_OK(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L /*, const std::string &name_space, const std::string &name*/)
			{
				std::string name_space = "OK";

				sol::state_view lua(L);
				sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					std::string name = "CommonIVal";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, OK::CommonIVal);
				}
				{
					std::string name = "CommonFunc";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, OK::CommonFunc);
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}
