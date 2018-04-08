#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/Geometry/GeometryUtils.h"

namespace SolLuaBind
{
	void LuaBind_GeometryUtils(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "GeometryUtils";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "DeltaAngle";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](const Vector3 & p0,const Vector3 & p1){ return GeometryUtils::DeltaAngle(p0,p1); },[](const Vector2 & p0,const Vector2 & p1){ return GeometryUtils::DeltaAngle(p0,p1); }));
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}