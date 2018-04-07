#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/AutoHeadOther.h"	
#include "AutoBind/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "OK";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
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
				{
					std::string name = "Test2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, OK::Test2);
				}				
				{
					std::string name = "Test3";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](int p0){ return OK::Test3(p0); },[](int p0,float p1){ return OK::Test3(p0,p1); }));
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}