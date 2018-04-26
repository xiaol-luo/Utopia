#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Geometry/GeometryDefine.h"	
#include "ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Circle(lua_State *L)
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
                std::string name = "Circle";
				std::string name_space = "";

				{
					sol::usertype<Circle> meta_table(
						sol::constructors<				
						Circle(),				
						Circle(const Vector2 &, float)
						>(),
						"__StructName__", sol::property([]() {return "Circle"; })				
						,"center", &Circle::center				
						,"radius", &Circle::radius				
						,"IsEmpty", &Circle::IsEmpty
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