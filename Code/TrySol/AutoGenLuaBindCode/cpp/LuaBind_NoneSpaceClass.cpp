#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "AutoBind/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_NoneSpaceClass(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "NoneSpaceClass";
				std::string name_space = "";

				{
					sol::usertype<NoneSpaceClass> meta_table(
					"__StructName__", sol::property([]() {return "NoneSpaceClass"; })				
						,"iVal", &NoneSpaceClass::iVal				
						,"Test", &NoneSpaceClass::Test
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