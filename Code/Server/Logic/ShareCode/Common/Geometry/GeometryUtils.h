
#pragma once

#include <stdint.h>
#include "GeometryDefine.h"

class Vector2;
class Vector3;

class GeometryUtils
{
public:
	static float DegToRad(float deg) { return deg * KPiOver180; }
	static float RadToDeg(float rad) { return rad * K180OverPi; }
	
	// 逆时针为正
	static float DeltaAngle(Vector3 from, Vector3 to);
	static float DeltaAngle(Vector2 from, Vector2 to);
	static Vector2 CalVector2(Vector2 from, float rotation);

	static void IsPointInRect(Vector2 &r1, Vector2 &r2, Vector2 &r3, Vector2 &r4, Vector2 &p1, Vector2 &p2, Vector2 &result);
	static bool IsLineSegmentIntersect(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2);
	static float GetLineIntersectPoint(Vector2 &a1, Vector2 &a2, Vector2 &b1, Vector2 &b2);
	static float Cross(Vector2 p1, Vector2 p2);
};


