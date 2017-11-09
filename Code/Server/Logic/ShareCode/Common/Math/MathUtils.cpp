
#include "MathUtils.h"
#include "Vector2.h"
#include "Vector3.h"

#include <stdlib.h>
#include <cassert>
#include <algorithm>

unsigned int MathUtils::NextPow2(unsigned int v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

float MathUtils::BitsToFloat(int i, int exponentBits, int mantissaBits)
{
	static int exponentSign[2] = { 1, -1 };
	int sign, exponent, mantissa, value;

	assert(exponentBits >= 2 && exponentBits <= 8);
	assert(mantissaBits >= 2 && mantissaBits <= 23);

	exponentBits--;
	sign = i >> (1 + exponentBits + mantissaBits);
	exponent = ((i >> mantissaBits) & ((1 << exponentBits) - 1)) * exponentSign[(i >> (exponentBits + mantissaBits)) & 1];
	mantissa = (i & ((1 << mantissaBits) - 1)) << (IEEE_FLT_MANTISSA_BITS - mantissaBits);
	value = sign << IEEE_FLT_SIGN_BIT | (exponent + IEEE_FLT_EXPONENT_BIAS) << IEEE_FLT_MANTISSA_BITS | mantissa;
	return *reinterpret_cast<float *>(&value);
}

int MathUtils::FloatToBits(float f, int exponentBits, int mantissaBits)
{
	int i, sign, exponent, mantissa, value;

	assert(exponentBits >= 2 && exponentBits <= 8);
	assert(mantissaBits >= 2 && mantissaBits <= 23);

	int maxBits = (((1 << (exponentBits - 1)) - 1) << mantissaBits) | ((1 << mantissaBits) - 1);
	int minBits = (((1 << exponentBits) - 2) << mantissaBits) | 1;

	float max = BitsToFloat(maxBits, exponentBits, mantissaBits);
	float min = BitsToFloat(minBits, exponentBits, mantissaBits);

	if (f >= 0.0f) {
		if (f >= max) {
			return maxBits;
		}
		else if (f <= min) {
			return minBits;
		}
	}
	else {
		if (f <= -max) {
			return (maxBits | (1 << (exponentBits + mantissaBits)));
		}
		else if (f >= -min) {
			return (minBits | (1 << (exponentBits + mantissaBits)));
		}
	}

	exponentBits--;
	i = *reinterpret_cast<int *>(&f);
	sign = (i >> IEEE_FLT_SIGN_BIT) & 1;
	exponent = ((i >> IEEE_FLT_MANTISSA_BITS) & ((1 << IEEE_FLT_EXPONENT_BITS) - 1)) - IEEE_FLT_EXPONENT_BIAS;
	mantissa = i & ((1 << IEEE_FLT_MANTISSA_BITS) - 1);
	value = sign << (1 + exponentBits + mantissaBits);
	value |= ((INTSIGNBITSET(exponent) << exponentBits) | (abs(exponent) & ((1 << exponentBits) - 1))) << mantissaBits;
	value |= mantissa >> (IEEE_FLT_MANTISSA_BITS - mantissaBits);
	return value;
}

float MathUtils::AngleFromVector3(const Vector3 &v)
{
	Vector2 vec2 = v.xz();
	return AngleFromVector2(vec2);
}

float MathUtils::AngleFromVector2(const Vector2 &v)
{
	Vector2 orig(0, 1);
	Vector2 current(v.x, v.y);
	current.normalize();

	float angle = (float)(acos(std::min(1.0f, std::max(-1.0f, orig | current))) * DEGREE_PER_RADIANS); // dot(a,b) = |a|*|b|*cos(angle) => cos(angle) = dot(a,b)/(|a|*|b|)
	return current.x > 0 ? angle : - angle;
}

void MathUtils::Angle2Vector(float degree, Vector3 &v)
{
	float radian = d2r(degree);
	v.x = -sin(radian);
	v.y = 0;
	v.z = cos(radian);
	return;

	if (degree >= 0 && degree <= 90) {// 0~90
		radian = d2r(degree);
		v.x = sin(radian);
		v.z = cos(radian);
		return;
	}
	else if (degree > 90 && degree <= 180) {// 90~180
		degree -= 90;
		radian = d2r(degree);
		v.x = cos(radian);
		v.z = -sin(radian);
		return;
	}
	else if (degree > 180 && degree <= 270) {// 180~270
		degree -= 180;
		radian = d2r(degree);
		v.x = -sin(radian);
		v.z = -cos(radian);
		return;
	}
	else if (degree > 270 && degree <= 360) {// 270~360
		degree -= 270;
		radian = d2r(degree);
		v.x = -cos(radian);
		v.z = sin(radian);
		return;
	}
	// never get here
	v = Vector3::zero;
}

Vector3 MathUtils::Angle2Vector(float degree)
{
	Vector3 ret; Angle2Vector(degree, ret); return ret;
}

float MathUtils::AngleLerp(float from, float to, float t)
{
	from = ClampDegree(from);
	to = ClampDegree(to);

	float delta = to - from;
	if (delta < -180)
		to += 360;
	if (delta > 180)
		to -= 360;

	return to * t + from * (1.0f - t);
}

float MathUtils::RotateTowards(float from, float to, float maxDegreeDelta)
{
	from = ClampDegree(from);
	to = ClampDegree(to);

	float delta = to - from;
	if (delta < -180)
		to += 360;
	if (delta > 180)
		to -= 360;

	delta = to - from;

	// land exactly on the target rather than overshoot
	if (fabsf(maxDegreeDelta) > fabsf(delta))
		return to;

	maxDegreeDelta = fabsf(maxDegreeDelta) * (delta < 0 ? -1 : 1);

	return ClampDegree(from + maxDegreeDelta);
}

float MathUtils::ClampDegree(float degree)
{
	float delta;
	while (degree < 0 || degree > 360)
	{
		delta = degree < 0 ? 360.0f : -360.0f;
		degree += delta;
	}
	return degree;
}

Vector3 MathUtils::Vector3Lerp(Vector3 from, Vector3 to, float t)
{
	return from * (1 - t) + to * t;
}

bool MathUtils::IsLineSegmentIntersect(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2)
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
float MathUtils::GetLineIntersectPoint(Vector2 &a1, Vector2 &a2, Vector2 &b1, Vector2 &b2)
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

//   r2-----r3
//    |		|
//	  |	 p1-|-----p2     
//   r1-----r4
void MathUtils::ClampPointInRect(Vector2 &r1, Vector2 &r2, Vector2 &r3, Vector2 &r4, Vector2 &p1, Vector2 &p2, Vector2 &result)
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

float MathUtils::Angle(Vector3 from, Vector3 to)
{
	Vector3  tmp_from(from);
	Vector3 tmp_to(to);
	tmp_from.normalize();
	tmp_to.normalize();
	Vector3 cross_vec3 = Vector3::cross(tmp_from, tmp_to);
	float cos_val = Vector3::dot(tmp_from, tmp_to);
	float angle = acos(cos_val) * DEGREE_PER_RADIANS;
	return cross_vec3.y >= 0 ? angle : -angle;
	// 这里cross_vec3.y > 0 则为逆时针，我以逆时针作为旋转正向
}

float MathUtils::Angle(Vector2 from, Vector2 to)
{
	return Angle(Vector3(from.x, 0, from.y), Vector3(to.x, 0, to.y));
}

Vector2 MathUtils::CalVector2(Vector2 from, float rotation)
{
	float radians = d2r(rotation);
	float x = from.x * cos(radians) + from.y * -sin(radians);
	float y = from.x * sin(radians) + from.y * cos(radians);
	return Vector2(x, y);
}

float MathUtils::Cross(Vector2 p1, Vector2 p2)
{
	return p1.x * p2.y - p2.x * p1.y;
}

float MathUtils::Random(float min, float max)
{
	return min + (rand() * (int)(max - min) / RAND_MAX);
}

