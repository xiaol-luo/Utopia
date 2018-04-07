#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "AutoBind/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK_Base(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Base";
				std::string name_space = "OK";

				{
					sol::usertype<OK::Base> meta_table(
					"__StructName__", sol::property([]() {return "Base"; })
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