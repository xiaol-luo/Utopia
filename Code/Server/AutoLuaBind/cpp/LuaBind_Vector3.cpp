#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/Vector3.h"	
#include "Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Vector3(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = const float *;
				static TypeAlias_1 toPointer1(const Vector3 &cls)
				{
					return cls.toPointer();
				}
				using TypeAlias_2 = float *;
				static TypeAlias_2 toPointer2(Vector3 &cls)
				{
					return cls.toPointer();
				}
				using TypeAlias_3 = void;
				static TypeAlias_3 Normalize1(Vector3 &cls)
				{
					return cls.Normalize();
				}
				using TypeAlias_4 = const Vector3 &;
				using TypeAlias_5 = Vector3;
				static TypeAlias_5 Normalize2(TypeAlias_4 p1)
				{
					return Vector3::Normalize(p1);
				}
				using TypeAlias_6 = float;
				using TypeAlias_7 = void;
				static TypeAlias_7 Scale1(Vector3 &cls, TypeAlias_6 p1)
				{
					return cls.Scale(p1);
				}
				using TypeAlias_8 = const Vector3 &;
				using TypeAlias_9 = float;
				using TypeAlias_10 = Vector3;
				static TypeAlias_10 Scale2(TypeAlias_8 p1, TypeAlias_9 p2)
				{
					return Vector3::Scale(p1, p2);
				}
				using TypeAlias_11 = void;
				static TypeAlias_11 Inverse1(Vector3 &cls)
				{
					return cls.Inverse();
				}
				using TypeAlias_12 = const Vector3 &;
				using TypeAlias_13 = Vector3;
				static TypeAlias_13 Inverse2(TypeAlias_12 p1)
				{
					return Vector3::Inverse(p1);
				}
			};
			
			struct ForPropertyField
			{
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
					{
						std::string var_name = "back";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::back);
					}				
					{
						std::string var_name = "down";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::down);
					}				
					{
						std::string var_name = "forward";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::forward);
					}				
					{
						std::string var_name = "left";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::left);
					}				
					{
						std::string var_name = "one";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::one);
					}				
					{
						std::string var_name = "right";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::right);
					}				
					{
						std::string var_name = "up";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::up);
					}				
					{
						std::string var_name = "zero";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::zero);
					}				
					{
						std::string var_name = "infinity";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector3::infinity);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}