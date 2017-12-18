#pragma once

struct Vector2
{
	float x, y;

	Vector2(const float *p) : x(p[0]), y(p[1]) {}
	Vector2() : x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y) { }

	float operator[] (int i);
	Vector2 operator + (const Vector2& inV) const;
	Vector2 operator - (const Vector2& inV) const;
	Vector2 operator * (const float s) const;
	Vector2 operator / (float s) const;
	Vector2 operator - () const;
	bool operator == (const Vector2& v) const;
	bool operator != (const Vector2& v) const;
	operator const float *() const;
	operator float *();
	
	void Set(float x, float y);
	void Inverse();
	void Scale(float scale);
	void Normalize();
	// the squared length of this vector
	float SqrMagnitude() const;
	// Returns the length of this vector
	float Magnitude() const;

	static float Dot(const Vector2 &lhs, const Vector2 &rhs);
	static Vector2 Cross(const Vector2 &lhs, const Vector2 &rhs); // ?
	static Vector2 Normalize(const Vector2 &val);
	static Vector2 Scale(const Vector2 &val, float scale);
	static Vector2 Inverse(const Vector2 &val);

	static const Vector2 infinity; // (inf, inf)
	static const Vector2 one; // (1, 1)
	static const Vector2 zero; // (0, 0)
	static const Vector2 left; // (-1, 0)
	static const Vector2 right; // (1, 0)
	static const Vector2 up; // (0, 1)
	static const Vector2 down; // (0, -1)
};
