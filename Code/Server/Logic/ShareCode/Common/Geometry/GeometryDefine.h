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
	Vector2 ltNode;
	Vector2 rbNode;
};

struct OBB2
{
	Vector2 center;
	float width = 0;
	float length = 0;
	Vector2 faceDir = 0;
};

struct Circle
{
	Vector2 center;
	float radius = 0;
};

struct Sector
{
	Vector2 center;
	float radius = 0;
	float halfAngle = 0;
};


