#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Common/Geometry/GeometryUtils.h"

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
					std::string name = "DeltaAngle";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::DeltaAngle);
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
					std::string name = "InFlatDistance";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GeometryUtils::InFlatDistance);
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
					std::string name = "RotateVector2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](const Vector2 & p0,float p1){ return GeometryUtils::RotateVector2(p0,p1); },[](const Vector2 & p0,const Vector2 & p1){ return GeometryUtils::RotateVector2(p0,p1); }));
				}				
				{
					std::string name = "IsPointInRect";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](Vector2 & p0,Vector2 & p1,Vector2 & p2,Vector2 & p3,Vector2 & p4,Vector2 & p5,Vector2 & p6){ return GeometryUtils::IsPointInRect(p0,p1,p2,p3,p4,p5,p6); },[](const Vector2 & p0,const Vector2 & p1,const Vector2 & p2){ return GeometryUtils::IsPointInRect(p0,p1,p2); }));
				}				
				{
					std::string name = "BuildAABB2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](const OBB2 & p0){ return GeometryUtils::BuildAABB2(p0); },[](const Circle & p0){ return GeometryUtils::BuildAABB2(p0); },[](const Sector & p0){ return GeometryUtils::BuildAABB2(p0); }));
				}				
				{
					std::string name = "AxisPointMoveRotate";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](const Axis2 & p0,const Axis2 & p1,const Vector2 * p2,size_t p3,Vector2 ** p4,size_t p5){ return GeometryUtils::AxisPointMoveRotate(p0,p1,p2,p3,p4,p5); },[](const Axis2 & p0,const Axis2 & p1,const Vector2 & p2,Vector2 & p3){ return GeometryUtils::AxisPointMoveRotate(p0,p1,p2,p3); }));
				}				
				{
					std::string name = "AxisPointRotateMove";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, sol::overload([](const Axis2 & p0,const Axis2 & p1,const Vector2 * p2,size_t p3,Vector2 ** p4,size_t p5){ return GeometryUtils::AxisPointRotateMove(p0,p1,p2,p3,p4,p5); },[](const Axis2 & p0,const Axis2 & p1,const Vector2 & p2,Vector2 & p3){ return GeometryUtils::AxisPointRotateMove(p0,p1,p2,p3); }));
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}