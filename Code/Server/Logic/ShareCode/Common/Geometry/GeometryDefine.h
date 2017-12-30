#pragma once

#include "Vector2.h"

const float KPi = 3.14159265f;
const float K2Pi = KPi * 2.0f;
const float KPiOver2 = KPi / 2.0f;
const float K1OverPi = 1.0f / KPi;
const float K1Over2Pi = 1.0f / K2Pi;
const float KPiOver180 = KPi / 180.0f;
const float K180OverPi = 180.0f / KPi;

struct AABB2
{
	Vector2 lt;
	Vector2 rb;

	bool IsEmpty() const { return lt == rb; }
};

struct OBB2
{
	Vector2 center;
	float x_size = 0;
	float y_size = 0;
	Vector2 y_axis_dir;

	bool IsEmpty() const { return 0 == x_size || 0 == y_size; }
	// Vector2 XAxis() { return GeometryUtils::RotateVector2(y_axis, -90); }
};

struct Circle
{
	Vector2 center;
	float radius = 0;

	bool IsEmpty() const { return radius <= 0; }
};

struct Sector
{
	Vector2 center;
	float radius = 0;
	float halfAngle = 0;
	Vector2 y_axis_dir;

	bool IsEmpty() const { return radius <= 0 || halfAngle <= 0; }
	// Vector2 XAxis() { return GeometryUtils::RotateVector2(y_axis, -90); }
};

struct Axis2
{
	Vector2 original_point;
	Vector2 direction;
};

struct LineSegment
{
	Vector2 p1;
	Vector2 p2;
};

