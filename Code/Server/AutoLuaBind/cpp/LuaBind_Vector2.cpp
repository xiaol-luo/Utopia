#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Vector2(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				static void Inverse1(Vector2 &cls)
				{
					return cls.Inverse();
				}
				static Vector2 Inverse2(const Vector2 & p1)
				{
					return Vector2::Inverse(p1);
				}
				static void Scale1(Vector2 &cls, float p1)
				{
					return cls.Scale(p1);
				}
				static Vector2 Scale2(const Vector2 & p1, float p2)
				{
					return Vector2::Scale(p1, p2);
				}
				static void Normalize1(Vector2 &cls)
				{
					return cls.Normalize();
				}
				static Vector2 Normalize2(const Vector2 & p1)
				{
					return Vector2::Normalize(p1);
				}
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Vector2";
				std::string name_space = "";

				{
					sol::usertype<Vector2> meta_table(
						sol::constructors<				
						Vector2(const float *),				
						Vector2(),				
						Vector2(float, float),				
						Vector2(const Vector2 &)
						>(),
					"__StructName__", sol::property([]() {return "Vector2"; })				
						,"x", &Vector2::x				
						,"y", &Vector2::y				
						,"operator[]", &Vector2::operator[]				
						,"operator=", &Vector2::operator=				
						,"operator+", &Vector2::operator+				
						,"operator*", &Vector2::operator*				
						,"operator/", &Vector2::operator/				
						,"operator==", &Vector2::operator==				
						,"operator!=", &Vector2::operator!=				
						,"Set", &Vector2::Set				
						,"SqrMagnitude", &Vector2::SqrMagnitude				
						,"Magnitude", &Vector2::Magnitude				
						,"Cross", &Vector2::Cross				
						,"Dot", &Vector2::Dot				
						,"Inverse", sol::overload(ForOverloadFns::Inverse1, ForOverloadFns::Inverse2)				
						,"Scale", sol::overload(ForOverloadFns::Scale1, ForOverloadFns::Scale2)				
						,"Normalize", sol::overload(ForOverloadFns::Normalize1, ForOverloadFns::Normalize2)
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					ns_table.set("infinity", Vector2::infinity);				
					ns_table.set("one", Vector2::one);				
					ns_table.set("zero", Vector2::zero);				
					ns_table.set("left", Vector2::left);				
					ns_table.set("right", Vector2::right);				
					ns_table.set("up", Vector2::up);				
					ns_table.set("down", Vector2::down);
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}