#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_OBB2(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				static Axis2 GetAxis1(OBB2 &cls)
				{
					return cls.GetAxis();
				}
				static Axis2 GetAxis2(const OBB2 &cls)
				{
					return cls.GetAxis();
				}
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "OBB2";
				std::string name_space = "";

				{
					sol::usertype<OBB2> meta_table(
						sol::constructors<				
						OBB2(),				
						OBB2(const Vector2 &, const Vector2 &, float, float)
						>(),
					"__StructName__", sol::property([]() {return "OBB2"; })				
						,"center", &OBB2::center				
						,"x_half_size", &OBB2::x_half_size				
						,"y_half_size", &OBB2::y_half_size				
						,"y_axis_dir", &OBB2::y_axis_dir				
						,"IsEmpty", &OBB2::IsEmpty				
						,"GetAxis", sol::overload(ForOverloadFns::GetAxis1, ForOverloadFns::GetAxis2)
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