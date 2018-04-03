#include "UserType/TryUserTypeUtil.h"
#include <sol.hpp>
#include "AutoBind/AutoHead.h"

namespace TryUserType
{
	void LuaBind_OK_OuterClass(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L /*, const std::string &name_space, const std::string &name*/)
			{
				std::string name_space = "OK";
				std::string name = "OuterClass";


				{
					sol::usertype<OK::OuterClass> meta_table(
						sol::constructors<\
						OK::OuterClass() \
						>(),
						"fval", &OK::OuterClass::fval,
						"inClass", &OK::OuterClass::inClass,
						// "TestOuterFun", &OK::OuterClass::TestOuterFun,
						"TestStaticFun", &OK::OuterClass::TestStaticFun,
						sol::base_classes, sol::bases<OK::Base>()
					);
					BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}

				{
					sol::table ns_table = GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];
					ns_table.set("siVal", OK::OuterClass::siVal);
				}

			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}
