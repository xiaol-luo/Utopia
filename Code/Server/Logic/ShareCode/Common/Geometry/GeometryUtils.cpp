
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
	tmp_from.Normalize();
	tmp_to.Normalize();
	Vector3 cross_vec3 = Vector3::Cross(tmp_from, tmp_to);
	float cos_val = Vector3::Dot(tmp_from, tmp_to);
	float angle = GeometryUtils::RadToDeg(acos(cos_val));
	return cross_vec3.y >= 0 ? angle : -angle; // 这里cross_vec3.y > 0 则为逆时针，我以逆时针作为旋转正向
}

float GeometryUtils::DeltaAngle(Vector2 from, Vector2 to)
{
	return DeltaAngle(Vector3(from.x, 0, from.y), Vector3(to.x, 0, to.y));
}

Vector2 GeometryUtils::RotateVector2(const Vector2 &from, float rotationDeg)
{
	float radians = GeometryUtils::DegToRad(rotationDeg);
	float x = from.x * cos(radians) + from.y * -sin(radians);
	float y = from.x * sin(radians) + from.y * cos(radians);
	return Vector2(x, y);
}

Vector2 GeometryUtils::RotateVector2(const Vector2 &from, const Vector2 &newYAxis)
{
	float angle = DeltaAngle(Vector2::up, newYAxis);
	return GeometryUtils::RotateVector2(from, angle);
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

bool GeometryUtils::IsIntersectLineSegment(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2)
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

bool GeometryUtils::IsIntersectCirlceRect(const Vector2 & circle_center, float radius, Vector2 rect_center, float length, float width)
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

	float l1 = Vector2::Dot(v, v);
	float l2 = radius *radius;
	return l1 < l2;
}

bool GeometryUtils::IsIntersectRectLineSegment(const Vector2 &r1, const Vector2 &r2, const Vector2 &lp1, const Vector2 &lp2)
{
	float min_x = std::min(r1.x, r2.x);
	float max_x = std::max(r1.x, r2.x);
	float min_y = std::min(r1.y, r2.y);
	float max_y = std::max(r1.y, r2.y);

	if (lp1.x >= min_x && lp1.x <= max_x && lp1.y >= min_y && lp1.y <= max_y)
		return true;
	if (lp2.x >= min_x && lp2.x <= max_x && lp2.y >= min_y && lp2.y <= max_y)
		return true;
	if (GeometryUtils::IsIntersectLineSegment(lp1, lp2, Vector2(min_x, min_y), Vector2(max_x, max_y)))
		return true;
	if (GeometryUtils::IsIntersectLineSegment(lp1, lp2, Vector2(min_x, max_y), Vector2(max_x, min_y)))
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

bool GeometryUtils::InFlatDistance(const Vector2 & from, const Vector2 & to, float distance)
{
	if (distance <= 0)
		return true;

	Vector2 delta = from; 
	delta = delta - to;
	float delta_sqr = delta.SqrMagnitude();
	return delta_sqr <= distance * distance;
}

bool GeometryUtils::InFlatDistance(const Vector3 & from, const Vector3 & to, float distance)
{
	return GeometryUtils::InFlatDistance(from.XZ(), to.XZ(), distance);
}

AABB2 GeometryUtils::BuildAABB2(const OBB2 & obb2)
{
	Vector2 v = Vector2(obb2.x_size / 2, obb2.y_size / 2);
	Vector2 v1 = RotateVector2(Vector2(v.x, v.y), obb2.y_dir);
	Vector2 v2 = RotateVector2(Vector2(-v.x, v.y), obb2.y_dir);
	Vector2 v3 = RotateVector2(Vector2(-v.x, -v.y), obb2.y_dir);
	Vector2 v4 = RotateVector2(Vector2(v.x, -v.y), obb2.y_dir);

	float xs[4] = { v1.x, v2.x, v3.x, v4.x };
	float ys[4] = { v1.y, v2.y, v3.y, v4.y };
	auto x_ret = std::minmax_element(&xs[0], &xs[4]);
	auto y_ret = std::minmax_element(&ys[0], &ys[4]);

	AABB2 ret;
	ret.lt = Vector2(*x_ret.first, *y_ret.first) + obb2.center;
	ret.rb = Vector2(*x_ret.second, *y_ret.second) + obb2.center;
	return ret;
}

AABB2 GeometryUtils::BuildAABB2(const Circle & circle2)
{
	AABB2 ret;
	ret.lt = circle2.center + Vector2(-circle2.radius, -circle2.radius);
	ret.rb = circle2.center + Vector2(circle2.radius, circle2.radius);
	return ret;
}

AABB2 GeometryUtils::BuildAABB2(const Sector & sector)
{
	float x_size = sector.radius * sin(sector.halfAngle);
	float y_size = sector.radius * cos(sector.halfAngle);
	Vector2 v1 = Vector2(0, 0);
	Vector2 v2 = RotateVector2(Vector2(0, sector.radius), sector.y_dir);
	Vector2 v3 = RotateVector2(Vector2(x_size, y_size), sector.y_dir);
	Vector2 v4 = RotateVector2(Vector2(-x_size, y_size), sector.y_dir);
	
	float xs[4] = { v1.x, v2.x, v3.x, v4.x };
	float ys[4] = { v1.y, v2.y, v3.y, v4.y };
	auto x_ret = std::minmax_element(&xs[0], &xs[4]);
	auto y_ret = std::minmax_element(&ys[0], &ys[4]);

	AABB2 ret;
	ret.lt = Vector2(*x_ret.first, *y_ret.first) + sector.center;
	ret.rb = Vector2(*x_ret.second, *y_ret.second) + sector.center;
	return ret;
}

static bool InRange(float val, float min_val, float max_val)
{
	return min_val <= val && val <= max_val;
}

bool GeometryUtils::IsIntersectAABB2(const AABB2 & l, const AABB2 & r)
{
	if (l.IsEmpty() || r.IsEmpty())
		return false;

	bool x_intersect = false;
	x_intersect = x_intersect | InRange(l.lt.x, r.lt.x, r.rb.x);
	x_intersect = x_intersect | InRange(l.rb.x, r.lt.x, r.rb.x);
	x_intersect = x_intersect | InRange(r.lt.x, l.lt.x, l.rb.x);
	x_intersect = x_intersect | InRange(r.rb.x, l.lt.x, l.rb.x);

	bool y_intersect = false;
	y_intersect = y_intersect | InRange(l.lt.y, r.lt.y, r.rb.y);
	y_intersect = y_intersect | InRange(l.rb.y, r.lt.y, r.rb.y);
	y_intersect = y_intersect | InRange(r.lt.y, l.lt.y, l.rb.y);
	y_intersect = y_intersect | InRange(r.rb.y, l.lt.y, l.rb.y);

	return x_intersect && y_intersect;
}

bool GeometryUtils::IsIncludeAABB2(const AABB2 & area, const AABB2 & target)
{
	if (area.IsEmpty())
		return false;

	bool ret = InRange(target.lt.x, area.lt.x, area.rb.x)
		&& InRange(target.rb.x, area.lt.x, area.rb.x)
		&& InRange(target.lt.y, area.lt.y, area.rb.y)
		&& InRange(target.rb.y, area.lt.y, area.rb.y);
	return ret;

}

bool GeometryUtils::CalIntersectAABB2(const AABB2 & l, const AABB2 & r, AABB2 * out)
{
	bool ret = GeometryUtils::IsIntersectAABB2(l, r);
	if (ret && nullptr != out)
	{
		AABB2 rect;
		rect.lt = Vector2(std::max(l.lt.x, r.lt.x), std::max(l.lt.y, r.lt.y));
		rect.rb = Vector2(std::min(l.rb.x, r.rb.x), std::min(l.rb.y, r.rb.y));
		*out = rect;
	}
	return ret;
}

bool GeometryUtils::IsIntersectCircle(const Circle & c1, const Circle & c2)
{
	return true;
}

bool GeometryUtils::IsIntersectObb2(const OBB2 & b1, const OBB2 & b2)
{
	return true;
}

bool GeometryUtils::IsIntersectSector(const Sector & s1, const Sector & s2)
{
	return true;
}

bool GeometryUtils::IsIntersectCircleOBB2(const Circle & circle, const OBB2 & obb2)
{
	return true;
}

bool GeometryUtils::IsIntersectCircleSector(const Circle & circle, const Sector & sector)
{
	return true;
}

bool GeometryUtils::IsIntersectObb2Sector(const OBB2 & obb2, const Sector & sector)
{
	return true;
}

