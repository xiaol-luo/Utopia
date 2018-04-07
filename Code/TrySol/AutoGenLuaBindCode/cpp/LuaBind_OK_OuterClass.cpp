#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "AutoBind/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK_OuterClass(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
                std::string name = "OuterClass";
				std::string name_space = "OK";

				{
					sol::usertype<OK::OuterClass> meta_table(
						sol::constructors<				
						OK::OuterClass() \
						>(),
					"__StructName__", sol::property([]() {return "OuterClass"; })				
						,"inClass", &OK::OuterClass::inClass				
						,"fval", &OK::OuterClass::fval				
						,"TestOuterFun", &OK::OuterClass::TestOuterFun				
						,"TestOverload", sol::overload([](OK::OuterClass &cls, int p0){ return cls.TestOverload(p0); },[](OK::OuterClass &cls, int p0,float p1){ return cls.TestOverload(p0,p1); })				
						, sol::base_classes, sol::bases<
							OK::Base \
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					ns_table.set("siVal", OK::OuterClass::siVal);				
					ns_table.set_function("TestStaticFun2", OK::OuterClass::TestStaticFun2);				
					ns_table.set_function("TestStaticFun", sol::overload([](int p0){ return OK::OuterClass::TestStaticFun(p0); },[](int p0,float p1){ return OK::OuterClass::TestStaticFun(p0,p1); }));	


				
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}