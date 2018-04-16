#pragma once

#include "Vector2.h"

const float KPi = 3.14159265f;
const float K2Pi = KPi * 2.0f;
const float KPiOver2 = KPi / 2.0f;
const float K1OverPi = 1.0f / KPi;
const float K1Over2Pi = 1.0f / K2Pi;
const float KPiOver180 = KPi / 180.0f;
const float K180OverPi = 180.0f / KPi;

struct Axis2
{
	Axis2() {}
	Axis2(const Vector2 &p, const Vector2 &dir)
		: original_point(p), direction(dir) {}

	bool IsValid() const;

	Vector2 original_point;
	Vector2 direction;

	static const Axis2 x_axis;
	static const Axis2 y_axis;
};

struct AABB2
{
	AABB2() {}
	AABB2(const Vector2 &_lt, const Vector2 &_rb)
		: lt(_lt), rb(_rb) {}

	Vector2 lt;
	Vector2 rb;

	bool IsEmpty() const { return lt == rb; }
};

struct OBB2
{
	OBB2() {}m
	OBB2(const Vector2 &_center, const Vector2 &_y_axis_dir, float _x_size, float _y_size)
		: center(_center), y_axis_dir(_y_axis_dir), x_half_size(_x_size), y_half_size(_y_size) {}

	Vector2 center;
	float x_half_size = 0;
	float y_half_size = 0;
	Vector2 y_axis_dir;

	bool IsEmpty() const { return x_half_size <= 0 || y_half_size <= 0; }
	Axis2 GetAxis() { return Axis2(center, y_axis_dir); }
	Axis2 GetAxis()const { return Axis2(center, y_axis_dir); }
};

struct Circle
{
	Circle() {}
	Circle(const Vector2 &_center, float _radius) 
		: center(_center),radius(_radius) {}

	Vector2 center;
	float radius = 0;

	bool IsEmpty() const { return radius <= 0; }
};

struct Sector
{
	Sector() {}
	Sector(const Vector2 &_center, float _radius, const Vector2 _y_axis_dir, float angle)
	 : center(_center), radius(_radius), y_axis_dir(_y_axis_dir), halfAngle(angle/2) {}

	Vector2 center;
	float radius = 0;
	float halfAngle = 0;
	Vector2 y_axis_dir;

	bool IsEmpty() const { return radius <= 0 || halfAngle <= 0; }
	// Vector2 XAxis() { return GeometryUtils::RotateVector2(y_axis, -90); }
};

struct LineSegment
{
	LineSegment() {}
	LineSegment(const Vector2 &_p1, const Vector2 _p2)
		: p1(_p1), p2(_p2) {}

	Vector2 p1;
	Vector2 p2;

	Vector2 * Points() { return &p1; }
};

