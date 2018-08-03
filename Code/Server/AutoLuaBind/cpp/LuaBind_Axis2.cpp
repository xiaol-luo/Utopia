#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/GeometryDefine.h"	
#include "Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Axis2(lua_State *L)
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
                std::string name = "Axis2";
				std::string name_space = "";

				{
					sol::usertype<Axis2> meta_table(
						sol::constructors<				
						Axis2(),				
						Axis2(const Vector2 &, const Vector2 &)
						>(),
						"__StructName__", sol::property([]() {return "Axis2"; })				
						,"original_point", &Axis2::original_point				
						,"direction", &Axis2::direction				
						,"IsValid", &Axis2::IsValid
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "x_axis";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Axis2::x_axis);
					}				
					{
						std::string var_name = "y_axis";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Axis2::y_axis);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}