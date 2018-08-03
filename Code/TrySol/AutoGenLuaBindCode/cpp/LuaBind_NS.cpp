#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/Test/fake2.h"	
#include "AutoBind/Test/fake_wrap.h"	
#include "AutoBind/Test/fake.h"

namespace SolLuaBind
{
	void LuaBind_NS(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "NS";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "Try";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, NS::Try);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}