#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/AutoHeadOther.h"	
#include "AutoBind/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "TestStr2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, TestStr2);
				}				
				{
					std::string name = "TestStr";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, TestStr);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}