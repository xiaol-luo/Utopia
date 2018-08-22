#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Geometry/GeometryDefine.h"	
#include "ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_AABB2(lua_State *L)
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
                std::string name = "AABB2";
				std::string name_space = "";

				{
					sol::usertype<AABB2> meta_table(
						sol::constructors<				
						AABB2(),				
						AABB2(const Vector2 &, const Vector2 &)
						>(),
						"__StructName__", sol::property([]() {return "AABB2"; })				
						,"lt", &AABB2::lt				
						,"rb", &AABB2::rb				
						,"IsEmpty", &AABB2::IsEmpty				
						,"Reset", &AABB2::Reset
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