#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Geometry/Vector3.h"

namespace SolLuaBind
{
	void LuaBind_Vector3(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				static const float * toPointer1(const Vector3 &cls)
				{
					return cls.toPointer();
				}
				static float * toPointer2(Vector3 &cls)
				{
					return cls.toPointer();
				}
				static void Normalize1(Vector3 &cls)
				{
					return cls.Normalize();
				}
				static Vector3 Normalize2(const Vector3 & p1)
				{
					return Vector3::Normalize(p1);
				}
				static void Scale1(Vector3 &cls, float p1)
				{
					return cls.Scale(p1);
				}
				static Vector3 Scale2(const Vector3 & p1, float p2)
				{
					return Vector3::Scale(p1, p2);
				}
				static void Inverse1(Vector3 &cls)
				{
					return cls.Inverse();
				}
				static Vector3 Inverse2(const Vector3 & p1)
				{
					return Vector3::Inverse(p1);
				}
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Vector3";
				std::string name_space = "";

				{
					sol::usertype<Vector3> meta_table(
						sol::constructors<				
						Vector3(const float *),				
						Vector3(),				
						Vector3(float, float, float),				
						Vector3(const Vector3 &)
						>(),
					"__StructName__", sol::property([]() {return "Vector3"; })				
						,"x", &Vector3::x				
						,"y", &Vector3::y				
						,"z", &Vector3::z				
						,"operator[]", &Vector3::operator[]				
						,"operator=", &Vector3::operator=				
						,"operator+", &Vector3::operator+				
						,"operator*", &Vector3::operator*				
						,"operator/", &Vector3::operator/				
						,"operator==", &Vector3::operator==				
						,"operator!=", &Vector3::operator!=				
						,"XZ", &Vector3::XZ				
						,"Set", &Vector3::Set				
						,"SqrMagnitude", &Vector3::SqrMagnitude				
						,"Magnitude", &Vector3::Magnitude				
						,"Cross", &Vector3::Cross				
						,"Dot", &Vector3::Dot				
						,"FromVector2", &Vector3::FromVector2				
						,"toPointer", sol::overload(ForOverloadFns::toPointer1, ForOverloadFns::toPointer2)				
						,"Normalize", sol::overload(ForOverloadFns::Normalize1, ForOverloadFns::Normalize2)				
						,"Scale", sol::overload(ForOverloadFns::Scale1, ForOverloadFns::Scale2)				
						,"Inverse", sol::overload(ForOverloadFns::Inverse1, ForOverloadFns::Inverse2)
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					ns_table.set("back", Vector3::back);				
					ns_table.set("down", Vector3::down);				
					ns_table.set("forward", Vector3::forward);				
					ns_table.set("left", Vector3::left);				
					ns_table.set("one", Vector3::one);				
					ns_table.set("right", Vector3::right);				
					ns_table.set("up", Vector3::up);				
					ns_table.set("zero", Vector3::zero);				
					ns_table.set("infinity", Vector3::infinity);
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}