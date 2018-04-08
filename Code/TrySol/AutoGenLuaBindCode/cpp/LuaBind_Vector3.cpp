#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/Geometry/Vector3.h"	
#include "AutoBind/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Vector3(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Vector3";
				std::string name_space = "";

				{
					sol::usertype<Vector3> meta_table(
					"__StructName__", sol::property([]() {return "Vector3"; })				
						,"x", &Vector3::x				
						,"y", &Vector3::y				
						,"z", &Vector3::z				
						,"XZ", &Vector3::XZ				
						,"FromVector2", &Vector3::FromVector2
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