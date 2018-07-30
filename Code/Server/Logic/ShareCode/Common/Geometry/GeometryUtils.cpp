
#include "GeometryUtils.h"
#include "Vector2.h"
#include "Vector3.h"
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <algorithm>
#include "Common/Utils/NumUtils.h"
#include <math.h>

float GeometryUtils::DegToRad(float deg)
{
	return deg * KPiOver180;
}

float GeometryUtils::RadToDeg(float rad)
{
	return rad * K180OverPi;
}

float GeometryUtils::DeltaAngle(const Vector3 &from, const Vector3 &to)
{
	Vector3  tmp_from(from);
	Vector3 tmp_to(to);
	tmp_from.Normalize();
	tmp_to.Normalize();
	Vector3 cross_vec3 = Vector3::Cross(tmp_from, tmp_to);
	float cos_val = Vector3::Dot(tmp_from, tmp_to);
	float angle = GeometryUtils::RadToDeg(acos(cos_val));
	return cross_vec3.y >= 0 ? angle : -angle; 
	// 使用左手坐标系，顺时针为旋转正方向
	// angle为正值表示拇指向+y，顺着四指方向旋转angle。
	// angle为负值表示拇指向-y，顺着四指方向旋转angle。
}

float GeometryUtils::DeltaAngle(const Vector2 &from, const Vector2 &to)
{
	float xx = DeltaAngle(Vector3(from.x, 0, from.y), Vector3(to.x, 0, to.y));
	float angle = 0;
	{
		float cos_val = Vector2::Dot(from, to) / (from.Magnitude() * to.Magnitude());
		cos_val = NumUtil::GetInRange(cos_val, -1.0f, 1.0f);
		angle = RadToDeg(acos(cos_val));



		// 原因：以顺时针方向为旋转角度正方向
		// sign > 0 to在from的左边（逆时针）, 根据"原因", angle取负
		// sign = 0 to和from同向或者反向
		// sign < 0 to在from的右边（顺时针），根据"原因", angle取正

		float sign = Vector2::Cross(from, to);
		if (sign > 0)
			angle = -angle;
	}
	return angle;
}

Vector2 GeometryUtils::RotateVector2(const Vector2 &from, float rotationDeg)
{
	// 因为顺时针为正，和书逆时针为正的假设刚刚相反。下边的计算方式来自书本
	rotationDeg = -rotationDeg; 
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
	if (Vector2::Cross(q1 - p1, p2 - p1)* Vector2::Cross(p2 - p1, q2 - p1) < 0)
	{
		return false;
	}
	if (Vector2::Cross(p1 - q1, q2 - q1)* Vector2::Cross(q2 - q1, p2 - q1) < 0)
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

bool GeometryUtils::IsIntersectCirlceRect(const Vector2 & circle_center, float radius, Vector2 rect_center, float x_size, float y_size)
{
	Vector2 tmp = circle_center;
	tmp = tmp - rect_center;

	Vector2 v = Vector2(abs(tmp.x), abs(tmp.y));
	Vector2 h = Vector2(x_size / 2, y_size / 2);
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
	Vector2 v = Vector2(obb2.x_half_size / 2, obb2.y_half_size / 2);
	Vector2 v1 = RotateVector2(Vector2(v.x, v.y), obb2.y_axis_dir);
	Vector2 v2 = RotateVector2(Vector2(-v.x, v.y), obb2.y_axis_dir);
	Vector2 v3 = RotateVector2(Vector2(-v.x, -v.y), obb2.y_axis_dir);
	Vector2 v4 = RotateVector2(Vector2(v.x, -v.y), obb2.y_axis_dir);

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
	Vector2 v2 = RotateVector2(Vector2(0, sector.radius), sector.y_axis_dir);
	Vector2 v3 = RotateVector2(Vector2(x_size, y_size), sector.y_axis_dir);
	Vector2 v4 = RotateVector2(Vector2(-x_size, y_size), sector.y_axis_dir);
	
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
	Vector2 o1o2 = c2.center - c1.center;
	bool is_intersect = o1o2.SqrMagnitude() < (c1.radius + c2.radius) * (c1.radius + c2.radius);
	return is_intersect;
}

bool GeometryUtils::IsIntersectObb2(const OBB2 & b1, const OBB2 & b2)
{
	static const int X_AXIS_ROTATE_DEGREE = 90;
	float min_val = 0, max_val = 0;
	{
		if (!ProjectOBB2OnAxis(Axis2(b1.center, b1.y_axis_dir), b2, &min_val, &max_val))
			return false;
		if (min_val > b1.y_half_size || max_val < -b1.y_half_size)
			return false;
		if (!ProjectOBB2OnAxis(Axis2(b1.center, RotateVector2(b1.y_axis_dir, X_AXIS_ROTATE_DEGREE)), b2, &min_val, &max_val))
			return false;
		if (min_val > b1.x_half_size || max_val < -b1.x_half_size)
			return false;
	}
	{
		if (!ProjectOBB2OnAxis(Axis2(b2.center, b2.y_axis_dir), b1, &min_val, &max_val))
			return false;
		if (min_val > b1.y_half_size || max_val < -b1.y_half_size)
			return false;
		if (!ProjectOBB2OnAxis(Axis2(b2.center, RotateVector2(b2.y_axis_dir, X_AXIS_ROTATE_DEGREE)), b1, &min_val, &max_val))
			return false;
		if (min_val > b1.y_half_size || max_val < -b1.y_half_size)
			return false;
	}
	return true;
}

bool GeometryUtils::IsIntersectSector(const Sector & s1, const Sector & s2)
{
	assert(false);
	return false;
}

bool GeometryUtils::IsIntersectCircleOBB2(const Circle & circle, const OBB2 & obb2)
{
	Vector2 object_point;
	if (!WorldAxisToObjectAxis(obb2.GetAxis(), circle.center, object_point))
		return false;

	return IsIntersectCirlceRect(object_point, circle.radius, Vector2::zero, obb2.x_half_size * 2, obb2.y_half_size * 2);
}

bool GeometryUtils::IsIntersectCircleSector(const Circle & circle, const Sector & sector)
{
	if (!IsIntersectCircle(circle, Circle(sector.center, sector.radius)))
		return false;

	if (std::abs(DeltaAngle(sector.y_axis_dir, circle.center - sector.center)) <= sector.halfAngle)
		return true;

	// 扇形弧中点-扇形圆心的向量
	Vector2 v = Vector2::Normalize(sector.y_axis_dir) * sector.radius; 
	LineSegment line = LineSegment(sector.center, sector.center + RotateVector2(v, sector.halfAngle));
	if (IsCircleIntersectLineSegment(circle, line))
		return true;
	line = LineSegment(sector.center, sector.center + RotateVector2(v, -sector.halfAngle));
	if (IsCircleIntersectLineSegment(circle, line))
		return true;
	return false;
}

bool GeometryUtils::IsIntersectObb2Sector(const OBB2 & obb2, const Sector & sector)
{
	assert(false);
	return false;
}

bool GeometryUtils::IsCircleIntersectLineSegment(const Circle & circle, const LineSegment & line_seg)
{
	Vector2 v1 = circle.center - line_seg.p1;
	Vector2 v2 = line_seg.p2 - line_seg.p1;

	float v2_len = v2.SqrMagnitude();
	float u = Vector2::Dot(v1, v2) / v2_len;

	Vector2 nearest_point;
	if (u <= 0)
		nearest_point = line_seg.p1;
	else if (u >= v2_len)
		nearest_point = line_seg.p2;
	else
		nearest_point = line_seg.p1 + Vector2::Normalize(v2) * u;

	Vector2 v3 = circle.center - nearest_point;
	return v3.Magnitude() < circle.radius * circle.radius;
}

bool GeometryUtils::WorldAxisToObjectAxis(const Axis2 &object_y_axis, const Vector2 & world_point, Vector2 & object_point)
{
	return AxisPointMoveRotate(Axis2::y_axis, object_y_axis, world_point, object_point);
}

bool GeometryUtils::ObjectAxisToWorldAxis(const Axis2 &object_y_axis, const Vector2 & object_point, Vector2 & world_point)
{
	return AxisPointRotateMove(object_y_axis, Axis2::y_axis, object_point, world_point);
}

bool GeometryUtils::ProjectPointOnAxis(const Axis2 & axis, const Vector2 & world_point, float * distance, Vector2 * projected_point)
{
	if (!axis.IsValid())
		return false;

	Vector2 object_point;
	bool ret = WorldAxisToObjectAxis(axis, world_point, object_point);
	if (!ret)
		return ret;

	if (nullptr != object_point)
	{
		*distance = object_point.y;
	}
	if (nullptr != projected_point)
	{
		Vector2 world_hit_point;
		ret = ObjectAxisToWorldAxis(axis, Vector2(0, object_point.y), world_hit_point);
		if (ret)
		{
			*projected_point = world_hit_point;
		}
	}
	return ret;
}

bool GeometryUtils::ProjectLineSegmentOnAxis(const Axis2 & axis, const LineSegment line_seg, LineSegment * projected_line_seg, float **projected_distances)
{
	if (axis.direction.SqrMagnitude() <= FLT_EPSILON)
		return false;

	Vector2 *ret_point2[2]; memset(ret_point2, 0, sizeof(ret_point2));
	float *ret_distances[2]; memset(ret_distances, 0, sizeof(ret_distances));

	if (nullptr != projected_line_seg)
	{
		ret_point2[0] = &projected_line_seg->p1;
		ret_point2[1] = &projected_line_seg->p2;
	}
	if (nullptr != projected_distances)
	{
		ret_distances[0] = projected_distances[0];
		ret_distances[1] = projected_distances[1];
	}
	if (!ProjectPointOnAxis(axis, line_seg.p1, ret_distances[0], ret_point2[0]))
		return false;
	if (!ProjectPointOnAxis(axis, line_seg.p2, ret_distances[1], ret_point2[1]))
		return false;
	return true;
}

bool GeometryUtils::ProjectAABBOnAxis(const Axis2 & axis, AABB2 rect, float * min_distance, float * max_distance)
{
	if (axis.direction.SqrMagnitude() <= FLT_EPSILON)
		return false;

	float ret_distances[4];
	ProjectPointOnAxis(axis, rect.lt, &ret_distances[0], nullptr);
	ProjectPointOnAxis(axis, rect.rb, &ret_distances[1], nullptr);
	ProjectPointOnAxis(axis, rect.lt + Vector2(rect.rb.x - rect.lt.x, 0), &ret_distances[2], nullptr);
	ProjectPointOnAxis(axis, rect.lt + Vector2(0, rect.rb.y - rect.lt.y), &ret_distances[4], nullptr);

	auto ret_min_max = std::minmax_element(ret_distances, ret_distances + 4);
	if (nullptr != min_distance)
		*min_distance = *ret_min_max.first;
	if (nullptr != max_distance)
		*max_distance = *ret_min_max.second;
	return true;
}

bool GeometryUtils::ProjectOBB2OnAxis(const Axis2 & axis, OBB2 rect, float * min_distance, float * max_distance)
{
	if (!axis.IsValid() || rect.y_axis_dir.SqrMagnitude() < FLT_EPSILON)
		return false;

	const static size_t OBB_POINTS = 4;
	Vector2 points[OBB_POINTS];
	points[0] = Vector2(-rect.x_half_size, -rect.y_half_size);		// lt
	points[1] = Vector2(rect.x_half_size, -rect.y_half_size);		// rt
	points[2] = Vector2(rect.x_half_size, rect.y_half_size);		// rb
	points[3] = Vector2(-rect.x_half_size, rect.y_half_size);		// lb

	Vector2 out_points[OBB_POINTS];
	Vector2 *p_out_points[OBB_POINTS];
	for (int i = 0; i < OBB_POINTS; ++i)
		p_out_points[i] = out_points + i;

	bool ret = AxisPointRotateMove(Axis2(rect.center, rect.y_axis_dir), axis, 
		points, OBB_POINTS, p_out_points, OBB_POINTS);

	float min_val = out_points[0].y;
	float max_val = out_points[0].y;
	for (int i = 1; i < OBB_POINTS; ++i)
	{
		if (out_points[i].y < min_val)
			min_val = out_points[i].y;
		if (out_points[i].y > max_val)
			max_val = out_points[i].y;
	}
	if (nullptr != min_distance)
		*min_distance = min_val;
	if (nullptr != max_distance)
		*max_distance = max_val;
	return true;
}

bool GeometryUtils::IsAxisValid(const Axis2 &axis)
{
	return axis.IsValid();
}

bool GeometryUtils::AxisPointMoveRotate(const Axis2 & old_axis, const Axis2 & new_axis, const Vector2 * old_points, size_t old_points_len, Vector2 ** out_points, size_t out_points_len)
{
	if (!IsAxisValid(old_axis) || !IsAxisValid(new_axis) || 
		nullptr == old_points || old_points_len <= 0 ||
		nullptr == out_points || out_points_len <= 0)
		return false;

	float delta_angle = DeltaAngle(old_axis.direction, new_axis.direction);
	Vector2 delta_v = new_axis.original_point - old_axis.original_point;
	bool need_rotate = std::abs(delta_angle) > FLT_EPSILON;
	for (size_t i = 0; i < old_points_len && i < out_points_len; ++i)
	{
		if (nullptr == out_points[i])
			continue;

		Vector2 p1 = old_points[i] - delta_v;			// 平移
		Vector2 p2 = p1;
		if (need_rotate)
			p2 = RotateVector2(p1, delta_angle);		// 旋转
		*(out_points[i]) = p2;
	}
	return true;
}

bool GeometryUtils::AxisPointMoveRotate(const Axis2 & old_axis, const Axis2 & new_axis, const Vector2 & old_point, Vector2 &out_point)
{
	Vector2 tmp; Vector2 *p_tmp = &tmp;
	bool ret = AxisPointMoveRotate(old_axis, new_axis, &old_point, 1, &p_tmp, 1);
	if (ret) out_point = tmp;
	return ret;
}

bool GeometryUtils::AxisPointRotateMove(const Axis2 & old_axis, const Axis2 & new_axis, const Vector2 * old_points, size_t old_points_len, Vector2 ** out_points, size_t out_points_len)
{
	if (!IsAxisValid(old_axis) || !IsAxisValid(new_axis) ||
		nullptr == old_points || old_points_len <= 0 ||
		nullptr == out_points || out_points_len <= 0)
		return false;

	float delta_angle = DeltaAngle(old_axis.direction, new_axis.direction);
	Vector2 delta_v = new_axis.original_point - old_axis.original_point;
	bool need_rotate = std::abs(delta_angle) > FLT_EPSILON;
	for (size_t i = 0; i < old_points_len && i < out_points_len; ++i)
	{
		if (nullptr == out_points[i])
			continue;

		Vector2 p1 = old_points[i];
		if (need_rotate)
			p1 = RotateVector2(p1, delta_angle);	// 旋转
		Vector2 p2 = p1 - delta_v;					// 平移
		*(out_points[i]) = p2;
	}
	return true;
}

bool GeometryUtils::AxisPointRotateMove(const Axis2 & old_axis, const Axis2 & new_axis, const Vector2 & old_point, Vector2 & out_point)
{
	Vector2 tmp; Vector2 *p_tmp = &tmp;
	bool ret = AxisPointRotateMove(old_axis, new_axis, &old_point, 1, &p_tmp, 1);
	if (ret) out_point = tmp;
	return ret;
}

bool GeometryUtils::IsIntersectProjectedAxisLineSegment(float o1, float o2, float p1, float p2)
{
	std::pair<float, float> o = std::minmax(01, 02);
	std::pair<float, float> p = std::minmax(p1, p2);

	if (p.second <= o.first || p.first >= o.second)
		return false;
	return true;
}



