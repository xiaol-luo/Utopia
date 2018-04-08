#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "AutoBind/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK_OuterClass(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				static void TestOverload1(const OK::OuterClass &cls, int p1)
				{
					return cls.TestOverload(p1);
				}
				static int TestOverload2(OK::OuterClass &cls, int p1)
				{
					return cls.TestOverload(p1);
				}
				static int TestOverload3(OK::OuterClass &cls, int p1, float p2)
				{
					return OK::OuterClass::TestOverload(p1, p2);
				}
				static int TestStaticFun1(OK::OuterClass &cls, int p1)
				{
					return OK::OuterClass::TestStaticFun(p1);
				}
				static int TestStaticFun2(OK::OuterClass &cls, int p1, float p2)
				{
					return OK::OuterClass::TestStaticFun(p1, p2);
				}
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "OuterClass";
				std::string name_space = "OK";

				{
					sol::usertype<OK::OuterClass> meta_table(
						sol::constructors<				
						OK::OuterClass()
						>(),
					"__StructName__", sol::property([]() {return "OuterClass"; })				
						,"inClass", &OK::OuterClass::inClass				
						,"fval", &OK::OuterClass::fval				
						,"TestOuterFun", &OK::OuterClass::TestOuterFun				
						,"TestStaticFun2", &OK::OuterClass::TestStaticFun2				
						,"TestOverload", sol::overload(ForOverloadFns::TestOverload1, ForOverloadFns::TestOverload2, ForOverloadFns::TestOverload3)				
						,"TestStaticFun", sol::overload(ForOverloadFns::TestStaticFun1, ForOverloadFns::TestStaticFun2)				
						, sol::base_classes, sol::bases<
							OK::Base 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					ns_table.set("siVal", OK::OuterClass::siVal);
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}