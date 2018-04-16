#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/AutoHead/AutoHead.h"

namespace SolLuaBind
{
	void LuaBind_OK_OuterClass_InnerClass(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "InnerClass";
				std::string name_space = "OK.OuterClass";

				{
					sol::usertype<OK::OuterClass::InnerClass> meta_table(
						"__StructName__", sol::property([]() {return "InnerClass"; })				
						,"ival", &OK::OuterClass::InnerClass::ival				
						,"TestInnerFunc", &OK::OuterClass::InnerClass::TestInnerFunc
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