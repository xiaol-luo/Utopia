#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/AutoHead/AutoHeadOther.h"	
#include "AutoBind/AutoHead/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = int;
				using TypeAlias_2 = void;
				static TypeAlias_2 Test31(TypeAlias_1 p1)
				{
					return OK::Test3(p1);
				}
				using TypeAlias_3 = int;
				using TypeAlias_4 = float;
				using TypeAlias_5 = void;
				static TypeAlias_5 Test32(TypeAlias_3 p1, TypeAlias_4 p2)
				{
					return OK::Test3(p1, p2);
				}
			};

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
					ns_table.set_function(name, sol::overload(ForOverloadFns::Test31, ForOverloadFns::Test32));
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}