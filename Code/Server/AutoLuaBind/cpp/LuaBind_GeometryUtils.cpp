#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/GeometryDefine.h"	
#include "Common/Geometry/Vector3.h"	
#include "Common/Geometry/Vector2.h"	
#include "Common/Geometry/GeometryUtils.h"

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
				using TypeAlias_7 = const Vector2 &;
				using TypeAlias_8 = float;
				using TypeAlias_9 = Vector2;
				static TypeAlias_9 RotateVector21(TypeAlias_7 p1, TypeAlias_8 p2)
				{
					return GeometryUtils::RotateVector2(p1, p2);
				}
				using TypeAlias_10 = const Vector2 &;
				using TypeAlias_11 = const Vector2 &;
				using TypeAlias_12 = Vector2;
				static TypeAlias_12 RotateVector22(TypeAlias_10 p1, TypeAlias_11 p2)
				{
					return GeometryUtils::RotateVector2(p1, p2);
				}
				using TypeAlias_13 = Vector2 &;
				using TypeAlias_14 = Vector2 &;
				using TypeAlias_15 = Vector2 &;
				using TypeAlias_16 = Vector2 &;
				using TypeAlias_17 = Vector2 &;
				using TypeAlias_18 = Vector2 &;
				using TypeAlias_19 = Vector2 &;
				using TypeAlias_20 = void;
				static TypeAlias_20 IsPointInRect1(TypeAlias_13 p1, TypeAlias_14 p2, TypeAlias_15 p3, TypeAlias_16 p4, TypeAlias_17 p5, TypeAlias_18 p6, TypeAlias_19 p7)
				{
					return GeometryUtils::IsPointInRect(p1, p2, p3, p4, p5, p6, p7);
				}
				using TypeAlias_21 = const Vector2 &;
				using TypeAlias_22 = const Vector2 &;
				using TypeAlias_23 = const Vector2 &;
				using TypeAlias_24 = bool;
				static TypeAlias_24 IsPointInRect2(TypeAlias_21 p1, TypeAlias_22 p2, TypeAlias_23 p3)
				{
					return GeometryUtils::IsPointInRect(p1, p2, p3);
				}
				using TypeAlias_25 = const Vector2 &;
				using TypeAlias_26 = const Vector2 &;
				using TypeAlias_27 = float;
				using TypeAlias_28 = bool;
				static TypeAlias_28 InFlatDistance1(TypeAlias_25 p1, TypeAlias_26 p2, TypeAlias_27 p3)
				{
					return GeometryUtils::InFlatDistance(p1, p2, p3);
				}
				using TypeAlias_29 = const Vector3 &;
				using TypeAlias_30 = const Vector3 &;
				using TypeAlias_31 = float;
				using TypeAlias_32 = bool;
				static TypeAlias_32 InFlatDistance2(TypeAlias_29 p1, TypeAlias_30 p2, TypeAlias_31 p3)
				{
					return GeometryUtils::InFlatDistance(p1, p2, p3);
				}
				using TypeAlias_33 = const OBB2 &;
				using TypeAlias_34 = AABB2;
				static TypeAlias_34 BuildAABB21(TypeAlias_33 p1)
				{
					return GeometryUtils::BuildAABB2(p1);
				}
				using TypeAlias_35 = const Circle &;
				using TypeAlias_36 = AABB2;
				static TypeAlias_36 BuildAABB22(TypeAlias_35 p1)
				{
					return GeometryUtils::BuildAABB2(p1);
				}
				using TypeAlias_37 = const Sector &;
				using TypeAlias_38 = AABB2;
				static TypeAlias_38 BuildAABB23(TypeAlias_37 p1)
				{
					return GeometryUtils::BuildAABB2(p1);
				}
				using TypeAlias_39 = const Axis2 &;
				using TypeAlias_40 = const Axis2 &;
				using TypeAlias_41 = const Vector2 *;
				using TypeAlias_42 = unsigned int;
				using TypeAlias_43 = Vector2 **;
				using TypeAlias_44 = unsigned int;
				using TypeAlias_45 = bool;
				static TypeAlias_45 AxisPointMoveRotate1(TypeAlias_39 p1, TypeAlias_40 p2, TypeAlias_41 p3, TypeAlias_42 p4, TypeAlias_43 p5, TypeAlias_44 p6)
				{
					return GeometryUtils::AxisPointMoveRotate(p1, p2, p3, p4, p5, p6);
				}
				using TypeAlias_46 = const Axis2 &;
				using TypeAlias_47 = const Axis2 &;
				using TypeAlias_48 = const Vector2 &;
				using TypeAlias_49 = Vector2 &;
				using TypeAlias_50 = bool;
				static TypeAlias_50 AxisPointMoveRotate2(TypeAlias_46 p1, TypeAlias_47 p2, TypeAlias_48 p3, TypeAlias_49 p4)
				{
					return GeometryUtils::AxisPointMoveRotate(p1, p2, p3, p4);
				}
				using TypeAlias_51 = const Axis2 &;
				using TypeAlias_52 = const Axis2 &;
				using TypeAlias_53 = const Vector2 *;
				using TypeAlias_54 = unsigned int;
				using TypeAlias_55 = Vector2 **;
				using TypeAlias_56 = unsigned int;
				using TypeAlias_57 = bool;
				static TypeAlias_57 AxisPointRotateMove1(TypeAlias_51 p1, TypeAlias_52 p2, TypeAlias_53 p3, TypeAlias_54 p4, TypeAlias_55 p5, TypeAlias_56 p6)
				{
					return GeometryUtils::AxisPointRotateMove(p1, p2, p3, p4, p5, p6);
				}
				using TypeAlias_58 = const Axis2 &;
				using TypeAlias_59 = const Axis2 &;
				using TypeAlias_60 = const Vector2 &;
				using TypeAlias_61 = Vector2 &;
				using TypeAlias_62 = bool;
				static TypeAlias_62 AxisPointRotateMove2(TypeAlias_58 p1, TypeAlias_59 p2, TypeAlias_60 p3, TypeAlias_61 p4)
				{
					return GeometryUtils::AxisPointRotateMove(p1, p2, p3, p4);
				}
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "GeometryUtils";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "DegToRad";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::DegToRad);
				}				
				{
					std::string name = "RadToDeg";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::RadToDeg);
				}				
				{
					std::string name = "IsIntersectLineSegment";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectLineSegment);
				}				
				{
					std::string name = "GetLineIntersectPoint";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::GetLineIntersectPoint);
				}				
				{
					std::string name = "IsIntersectCirlceRect";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectCirlceRect);
				}				
				{
					std::string name = "IsIntersectRectLineSegment";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectRectLineSegment);
				}				
				{
					std::string name = "IsIntersectAABB2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectAABB2);
				}				
				{
					std::string name = "IsIncludeAABB2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIncludeAABB2);
				}				
				{
					std::string name = "CalIntersectAABB2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::CalIntersectAABB2);
				}				
				{
					std::string name = "IsIntersectCircle";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectCircle);
				}				
				{
					std::string name = "IsIntersectObb2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectObb2);
				}				
				{
					std::string name = "IsIntersectSector";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectSector);
				}				
				{
					std::string name = "IsIntersectCircleOBB2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectCircleOBB2);
				}				
				{
					std::string name = "IsIntersectCircleSector";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectCircleSector);
				}				
				{
					std::string name = "IsIntersectObb2Sector";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectObb2Sector);
				}				
				{
					std::string name = "IsCircleIntersectLineSegment";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsCircleIntersectLineSegment);
				}				
				{
					std::string name = "WorldAxisToObjectAxis";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::WorldAxisToObjectAxis);
				}				
				{
					std::string name = "ObjectAxisToWorldAxis";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::ObjectAxisToWorldAxis);
				}				
				{
					std::string name = "ProjectPointOnAxis";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::ProjectPointOnAxis);
				}				
				{
					std::string name = "ProjectLineSegmentOnAxis";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::ProjectLineSegmentOnAxis);
				}				
				{
					std::string name = "ProjectAABBOnAxis";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::ProjectAABBOnAxis);
				}				
				{
					std::string name = "ProjectOBB2OnAxis";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::ProjectOBB2OnAxis);
				}				
				{
					std::string name = "IsAxisValid";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsAxisValid);
				}				
				{
					std::string name = "IsIntersectProjectedAxisLineSegment";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::IsIntersectProjectedAxisLineSegment);
				}				
				{
					std::string name = "DeltaAngle";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::DeltaAngle1, ForOverloadFns::DeltaAngle2));
				}				
				{
					std::string name = "RotateVector2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::RotateVector21, ForOverloadFns::RotateVector22));
				}				
				{
					std::string name = "IsPointInRect";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::IsPointInRect1, ForOverloadFns::IsPointInRect2));
				}				
				{
					std::string name = "InFlatDistance";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::InFlatDistance1, ForOverloadFns::InFlatDistance2));
				}				
				{
					std::string name = "BuildAABB2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::BuildAABB21, ForOverloadFns::BuildAABB22, ForOverloadFns::BuildAABB23));
				}				
				{
					std::string name = "AxisPointMoveRotate";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::AxisPointMoveRotate1, ForOverloadFns::AxisPointMoveRotate2));
				}				
				{
					std::string name = "AxisPointRotateMove";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload(ForOverloadFns::AxisPointRotateMove1, ForOverloadFns::AxisPointRotateMove2));
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}