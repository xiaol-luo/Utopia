#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "ShareCode/Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_LineSegment(lua_State *L)
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
                std::string name = "LineSegment";
				std::string name_space = "";

				{
					sol::usertype<LineSegment> meta_table(
						sol::constructors<				
						LineSegment(),				
						LineSegment(const Vector2 &, const Vector2)
						>(),
						"__StructName__", sol::property([]() {return "LineSegment"; })				
						,"p1", &LineSegment::p1				
						,"p2", &LineSegment::p2				
						,"Points", &LineSegment::Points
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