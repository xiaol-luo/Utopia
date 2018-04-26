#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Geometry/GeometryDefine.h"	
#include "ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Sector(lua_State *L)
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
                std::string name = "Sector";
				std::string name_space = "";

				{
					sol::usertype<Sector> meta_table(
						sol::constructors<				
						Sector(),				
						Sector(const Vector2 &, float, const Vector2, float)
						>(),
						"__StructName__", sol::property([]() {return "Sector"; })				
						,"center", &Sector::center				
						,"radius", &Sector::radius				
						,"halfAngle", &Sector::halfAngle				
						,"y_axis_dir", &Sector::y_axis_dir				
						,"IsEmpty", &Sector::IsEmpty
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