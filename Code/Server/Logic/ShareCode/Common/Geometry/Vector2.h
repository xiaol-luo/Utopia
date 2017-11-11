#pragma once

class Vector2
{
public:
	Vector2(const float *p)
		: x(p[0]), y(p[1]) {}
	Vector2() : x(0), y(0) {}
	Vector2(float _x, float _y)
		: x(_x), y(_y) { }

	float operator[] (int i);
	Vector2 operator + (const Vector2& inV);
	Vector2 operator - (const Vector2& inV);
	Vector2 operator * (const float s);
	Vector2 operator / (float s);
	bool operator == (const Vector2& v)const;

	Vector2 operator -() const;

	Vector2 scale(const Vector2& inV);
	float sqrMagnitude();
	float magnitude();
	void normalize();
	void set(float x, float y);
	Vector2 inverse();
	float angle(Vector2& rhs);
	Vector2 rotate(float radian);

	static float dot(const Vector2 &lhs, const Vector2& rhs);

	static Vector2 cInfinity() { return infinity; }
	static Vector2 cOne() { return one; }
	static Vector2 cZero() { return zero; }
	static Vector2 cLeft() { return left; }
	static Vector2 cRight() { return right; }
	static Vector2 cUp() { return up; }
	static Vector2 cDown() { return down; }

	bool operator != (const Vector2& v)const;
	float operator|(const Vector2 &rhs) const { return dot(*this, rhs); }

	operator const float *() const;
	operator float *();

public:
	float x, y;
	
	static const Vector2 infinity; // (inf, inf)
	static const Vector2 one; // (1, 1)
	static const Vector2 zero; // (0, 0)
	static const Vector2 left; // (-1, 0)
	static const Vector2 right; // (1, 0)
	static const Vector2 up; // (0, 1)
	static const Vector2 down; // (0, -1)
}; // tolua_export
