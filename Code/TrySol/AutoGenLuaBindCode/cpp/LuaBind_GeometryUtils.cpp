#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/Geometry/GeometryUtils.h"	
#include "AutoBind/Geometry/Vector2.h"	
#include "AutoBind/Geometry/Vector3.h"

namespace SolLuaBind
{
	void LuaBind_GeometryUtils(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = const Vector3 &;
				using TypeAlias_2 = const Vector3 &;
				using TypeAlias_3 = float;
				static TypeAlias_3 DeltaAngle1(TypeAlias_1 p1, TypeAlias_2 p2)
				{
					return GeometryUtils::DeltaAngle(p1, p2);
				}
				using TypeAlias_4 = const Vector2 &;
				using TypeAlias_5 = const Vector2 &;
				using TypeAlias_6 = float;
				static TypeAlias_6 DeltaAngle2(TypeAlias_4 p1, TypeAlias_5 p2)
				{
					return GeometryUtils::DeltaAngle(p1, p2);
				}
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "GeometryUtils";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "DeltaAngle";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::DeltaAngle1, ForOverloadFns::DeltaAngle2));
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}