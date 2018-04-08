#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "AutoBind/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Vector2(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Vector2";
				std::string name_space = "";

				{
					sol::usertype<Vector2> meta_table(
					"__StructName__", sol::property([]() {return "Vector2"; })				
						,"x", &Vector2::x				
						,"y", &Vector2::y
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