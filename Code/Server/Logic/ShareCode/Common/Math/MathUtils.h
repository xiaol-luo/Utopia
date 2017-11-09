
#pragma once

#include <stdint.h>



#define FLOATSIGNBITSET(f)		((*(const unsigned long *)&(f)) >> 31)
#define FLOATSIGNBITNOTSET(f)	((~(*(const unsigned long *)&(f))) >> 31)
#define FLOATNOTZERO(f)			((*(const unsigned long *)&(f)) & ~(1<<31) )
#define INTSIGNBITSET(i)		(((const unsigned long)(i)) >> 31)
#define INTSIGNBITNOTSET(i)		((~((const unsigned long)(i))) >> 31)

#define IEEE_FLT_MANTISSA_BITS	23
#define IEEE_FLT_EXPONENT_BITS	8
#define IEEE_FLT_EXPONENT_BIAS	127
#define IEEE_FLT_SIGN_BIT		31

#define IEEE_DBL_MANTISSA_BITS	52
#define IEEE_DBL_EXPONENT_BITS	11
#define IEEE_DBL_EXPONENT_BIAS	1023
#define IEEE_DBL_SIGN_BIT		63

#define IEEE_DBLE_MANTISSA_BITS	63
#define IEEE_DBLE_EXPONENT_BITS	15
#define IEEE_DBLE_EXPONENT_BIAS	0
#define IEEE_DBLE_SIGN_BIT		79

#define PI						(3.14159265358979323846)
#define RADIANS_PER_DEGREE		(PI/180.0)
#define DEGREE_PER_RADIANS		(180.0/PI)
#define EPS						0.000001

class MathUtils
{
public:
	static unsigned int NextPow2(unsigned int v);

	static float BitsToFloat(int i, int exponentBits, int mantissaBits);

	static int FloatToBits(float f, int exponentBits, int mantissaBits);

	static int Angle2byte(float x) { return (int(x * 256.0f / 360.0f)) & 255; }
	static float Byte2angle(int x) { return x * 360.0f / 256.0f; }

	static float d2r(float degree) { return (float)(degree * RADIANS_PER_DEGREE); }
	static float r2d(float radian) { return (float)(radian * DEGREE_PER_RADIANS); }
	static float Random(float min, float max);

	// angle functions
	static float AngleFromVector3(const class Vector3 &v); // clock-wise
	static float AngleFromVector2(const class Vector2 &v);

	// in common situation, we would take the degree as a quaternion, then using quaternion * vector3 to apply the rotation
	// but in the current situation, we can do some optimization for fast calculation because the origin vector is (0,0,1), which narrow the usage
	static void Angle2Vector(float degree, Vector3 &v);
	static Vector3 Angle2Vector(float degree);
	static float AngleLerp(float from, float to, float t);
	static float RotateTowards(float from, float to, float maxDegreeDelta);
	static float ClampDegree(float degree);
	static Vector3 Vector3Lerp(Vector3 from, Vector3 to, float t);
	static bool IsLineSegmentIntersect(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2);
	static float GetLineIntersectPoint(Vector2 &a1, Vector2 &a2, Vector2 &b1, Vector2 &b2);
	static float Mult(Vector2 a, Vector2 b, Vector2 c);
	static float Cross(Vector2 p1, Vector2 p2);

	static void ClampPointInRect(Vector2 &r1, Vector2 &r2, Vector2 &r3, Vector2 &r4, Vector2 &p1, Vector2 &p2, Vector2 &result);

	template<typename T>
	static T Clamp(T v, T min, T max)
	{
		return v < min ? min : v > max ? max : v;
	}

	template<typename T>
	static T Saturate(T v)
	{
		return Clamp<T>(v, 0, 1);
	}

	static inline uint32_t ZigZagEncode32(int n)
	{
		// Note:  the right-shift must be arithmetic
		return (static_cast<uint32_t>(n) << 1) ^ (n >> 31);
	}

	static inline int ZigZagDecode32(uint32_t n)
	{
		return (n >> 1) ^ -static_cast<int>(n & 1);
	}

	static inline uint64_t ZigZagEncode64(int64_t n)
	{
		// Note:  the right-shift must be arithmetic
		return (static_cast<uint64_t>(n) << 1) ^ (n >> 63);
	}

	static inline int64_t ZigZagDecode64(uint64_t n)
	{
		return (n >> 1) ^ -static_cast<int64_t>(n & 1);
	}

	static inline int ZigZag(int n)
	{
		return (n >> 1) ^ -static_cast<int>(n & 1);
	}

	// 逆时针为正
	static float Angle(Vector3 from, Vector3 to);
	static float Angle(Vector2 from, Vector2 to);
	static Vector2 CalVector2(Vector2 from, float rotation); 
};


