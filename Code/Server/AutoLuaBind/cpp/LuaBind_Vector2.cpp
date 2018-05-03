#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_Vector2(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = void;
				static TypeAlias_1 Inverse1(Vector2 &cls)
				{
					return cls.Inverse();
				}
				using TypeAlias_2 = const Vector2 &;
				using TypeAlias_3 = Vector2;
				static TypeAlias_3 Inverse2(TypeAlias_2 p1)
				{
					return Vector2::Inverse(p1);
				}
				using TypeAlias_4 = float;
				using TypeAlias_5 = void;
				static TypeAlias_5 Scale1(Vector2 &cls, TypeAlias_4 p1)
				{
					return cls.Scale(p1);
				}
				using TypeAlias_6 = const Vector2 &;
				using TypeAlias_7 = float;
				using TypeAlias_8 = Vector2;
				static TypeAlias_8 Scale2(TypeAlias_6 p1, TypeAlias_7 p2)
				{
					return Vector2::Scale(p1, p2);
				}
				using TypeAlias_9 = void;
				static TypeAlias_9 Normalize1(Vector2 &cls)
				{
					return cls.Normalize();
				}
				using TypeAlias_10 = const Vector2 &;
				using TypeAlias_11 = Vector2;
				static TypeAlias_11 Normalize2(TypeAlias_10 p1)
				{
					return Vector2::Normalize(p1);
				}
			};
			
			struct ForPropertyField
			{
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
					{
						std::string var_name = "infinity";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::infinity);
					}				
					{
						std::string var_name = "one";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::one);
					}				
					{
						std::string var_name = "zero";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::zero);
					}				
					{
						std::string var_name = "left";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::left);
					}				
					{
						std::string var_name = "right";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::right);
					}				
					{
						std::string var_name = "up";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::up);
					}				
					{
						std::string var_name = "down";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, Vector2::down);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}