
#include "GeometryUtils.h"
#include "Vector2.h"
#include "Vector3.h"

#include <stdlib.h>
#include <cassert>
#include <algorithm>



float GeometryUtils::DegToRad(float deg)
{
	return deg * KPiOver180;
}

float GeometryUtils::RadToDeg(float rad)
{
	return rad * K180OverPi;
}

float GeometryUtils::DeltaAngle(Vector3 from, Vector3 to)
{
	Vector3  tmp_from(from);
	Vector3 tmp_to(to);
	tmp_from.normalize();
	tmp_to.normalize();
	Vector3 cross_vec3 = Vector3::cross(tmp_from, tmp_to);
	float cos_val = Vector3::dot(tmp_from, tmp_to);
	float angle = GeometryUtils::RadToDeg(acos(cos_val));
	return cross_vec3.y >= 0 ? angle : -angle; // 这里cross_vec3.y > 0 则为逆时针，我以逆时针作为旋转正向
}

float GeometryUtils::DeltaAngle(Vector2 from, Vector2 to)
{
	return DeltaAngle(Vector3(from.x, 0, from.y), Vector3(to.x, 0, to.y));
}

Vector2 GeometryUtils::CalVector2(Vector2 from, float rotation)
{
	float radians = GeometryUtils::DegToRad(rotation);
	float x = from.x * cos(radians) + from.y * -sin(radians);
	float y = from.x * sin(radians) + from.y * cos(radians);
	return Vector2(x, y);
}

float GeometryUtils::Cross(Vector2 p1, Vector2 p2)
{
	return p1.x * p2.y - p2.x * p1.y;
}

//   r2-----r3
//    |		|
//	  |	 p1-|-----p2     
//   r1-----r4
void GeometryUtils::IsPointInRect(Vector2 &r1, Vector2 &r2, Vector2 &r3, Vector2 &r4, Vector2 &p1, Vector2 &p2, Vector2 &result)
{
	result = p2;
	float f;
	// check p1p2 with r1r2
	f = GetLineIntersectPoint(p1, p2, r1, r2);
	if (f >= 0 && f <= 1) {
		result = p1 + (p2 - p1)*f;
		//g_hostImport.logOut(LogType::Log, "intersect with r1r2");
		return;
	}
	// check p1p2 with r2r3
	f = GetLineIntersectPoint(p1, p2, r2, r3);
	if (f >= 0 && f <= 1) {
		result = p1 + (p2 - p1)*f;
		//g_hostImport.logOut(LogType::Log, "intersect with r2r3");
		return;
	}
	// check p1p2 with r3r4
	f = GetLineIntersectPoint(p1, p2, r3, r4);
	if (f >= 0 && f <= 1) {
		result = p1 + (p2 - p1)*f;
		//g_hostImport.logOut(LogType::Log, "intersect with r3r4");
		return;
	}
	// check p1p2 with r1r4
	f = GetLineIntersectPoint(p1, p2, r1, r4);
	if (f >= 0 && f <= 1) {
		result = p1 + (p2 - p1)*f;
		//g_hostImport.logOut(LogType::Log, "intersect with r1r4");
		return;
	}
}

bool GeometryUtils::IsLineSegmentIntersect(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2)
{
	if (std::max(p1.x, p2.x) < std::min(q1.x, q2.x))
	{
		return false;
	}
	if (std::max(p1.y, p2.y) < std::min(q1.y, q2.y))
	{
		return false;
	}
	if (std::max(q1.x, q2.x) < std::min(p1.x, p2.x))
	{
		return false;
	}
	if (std::max(q1.y, q2.y) < std::min(p1.y, p2.y))
	{
		return false;
	}
	if (Cross(q1 - p1, p2 - p1)*Cross(p2 - p1, q2 - p1) < 0)
	{
		return false;
	}
	if (Cross(p1 - q1, q2 - q1)*Cross(q2 - q1, p2 - q1) < 0)
	{
		return false; 
	}

	return true;
}

// if return -1, line segment not intersect
// if return ret -> [0, 1] intersect point = a1 + ret * (a2 - a1) 
float GeometryUtils::GetLineIntersectPoint(Vector2 &a1, Vector2 &a2, Vector2 &b1, Vector2 &b2)
{
	float denom = ((b2.y - b1.y) * (a2.x - a1.x)) - ((b2.x - b1.x) * (a2.y - a1.y));
	if (denom == 0)
		return -1;
	else {
		float ua = (((b2.x - b1.x) * (a1.y - b1.y)) - ((b2.y - b1.y) * (a1.x - b1.x))) / denom;
		/* The following 3 lines are only necessary if we are checking line
		segments instead of infinite-length lines */
		float ub = (((a2.x - a1.x) * (a1.y - b1.y)) - ((a2.y - a1.y) * (a1.x - b1.x))) / denom;
		if ((ua < 0) || (ua > 1) || (ub < 0) || (ub > 1))
			return -1;

		return ua;
	}
	return -1;
}

bool GeometryUtils::IsCirlceRectIntersect(const Vector2 & circle_center, float radius, Vector2 rect_center, float length, float width)
{
	Vector2 tmp = circle_center;
	tmp = tmp - rect_center;

	Vector2 v = Vector2(abs(tmp.x), abs(tmp.y));
	Vector2 h = Vector2(length / 2, width / 2);
	v = v - h;
	if (v.x < FLT_MIN)
		v.x = 0;
	if (v.y < FLT_MIN)
		v.y = 0;

	float l1 = Vector2::dot(v, v);
	float l2 = radius *radius;
	return l1 < l2;
}

bool GeometryUtils::IsRectLineSegmentIntersect(const Vector2 &r1, const Vector2 &r2, const Vector2 &lp1, const Vector2 &lp2)
{
	float min_x = std::min(r1.x, r2.x);
	float max_x = std::max(r1.x, r2.x);
	float min_y = std::min(r1.y, r2.y);
	float max_y = std::max(r1.y, r2.y);

	if (lp1.x >= min_x && lp1.x <= max_x && lp1.y >= min_y && lp1.y <= max_y)
		return true;
	if (lp2.x >= min_x && lp2.x <= max_x && lp2.y >= min_y && lp2.y <= max_y)
		return true;
	if (GeometryUtils::IsLineSegmentIntersect(lp1, lp2, Vector2(min_x, min_y), Vector2(max_x, max_y)))
		return true;
	if (GeometryUtils::IsLineSegmentIntersect(lp1, lp2, Vector2(min_x, max_y), Vector2(max_x, min_y)))
		return true;
	return false;
}

bool GeometryUtils::IsPointInRect(const Vector2 & r1, const Vector2 & r2, const Vector2 & p)
{
	float min_x = std::min(r1.x, r2.x);
	float max_x = std::max(r1.x, r2.x);
	float min_y = std::min(r1.y, r2.y);
	float max_y = std::max(r1.y, r2.y);
	return p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y;
}
