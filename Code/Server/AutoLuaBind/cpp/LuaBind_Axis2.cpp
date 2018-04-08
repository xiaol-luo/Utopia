#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_Axis2(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
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
					ns_table.set("x_axis", Axis2::x_axis);				
					ns_table.set("y_axis", Axis2::y_axis);
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}