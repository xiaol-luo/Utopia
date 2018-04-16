#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/AutoHead/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK_OuterClass(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = int;
				using TypeAlias_2 = void;
				static TypeAlias_2 TestOverload1(const OK::OuterClass &cls, TypeAlias_1 p1)
				{
					return cls.TestOverload(p1);
				}
				using TypeAlias_3 = int;
				using TypeAlias_4 = int;
				static TypeAlias_4 TestOverload2(OK::OuterClass &cls, TypeAlias_3 p1)
				{
					return cls.TestOverload(p1);
				}
				using TypeAlias_5 = int;
				using TypeAlias_6 = float;
				using TypeAlias_7 = int;
				static TypeAlias_7 TestOverload3(TypeAlias_5 p1, TypeAlias_6 p2)
				{
					return OK::OuterClass::TestOverload(p1, p2);
				}
				using TypeAlias_8 = int;
				using TypeAlias_9 = int;
				static TypeAlias_9 TestStaticFun1(TypeAlias_8 p1)
				{
					return OK::OuterClass::TestStaticFun(p1);
				}
				using TypeAlias_10 = int;
				using TypeAlias_11 = float;
				using TypeAlias_12 = int;
				static TypeAlias_12 TestStaticFun2(TypeAlias_10 p1, TypeAlias_11 p2)
				{
					return OK::OuterClass::TestStaticFun(p1, p2);
				}
			};
			
			struct ForPropertyField
			{
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
					{
						std::string var_name = "siVal";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, OK::OuterClass::siVal);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}