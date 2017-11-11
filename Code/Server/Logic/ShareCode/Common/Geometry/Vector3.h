#pragma once

class Vector2;

class Vector3
{
public:
	explicit Vector3(const float *p)
		: x(p[0]), y(p[1]), z(p[2]) {}
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) { }

	float operator[](int index) const;
	Vector3 operator+(const Vector3 &other) const;
	Vector3 operator-(const Vector3 &other) const;
	Vector3 operator*(const Vector3 &other) const;
	Vector3 operator*(float scale) const;
	Vector3 operator/(float scale) const;
	Vector3 operator/(const Vector3 &other) const;
	Vector3 operator-() const;
	bool operator==(const Vector3 &other) const;

	float magnitude() const;
	void normalize();
	Vector3 normalized() const;
	float sqrMagnitude() const;
	void set(float x, float y, float z);
	Vector2 xz() const;


	static Vector3 cross(const Vector3 &lhs, const Vector3 &rhs);
	static float dot(const Vector3 &lhs, const Vector3 &rhs);
	static Vector3 moveTowards(const Vector3 &current, const Vector3 &target, float maxDistanceDelta);

	static Vector3 cBack() { return back; }
	static Vector3 cDown() { return down; }
	static Vector3 cForward() { return forward; }
	static Vector3 cLeft() { return left; }
	static Vector3 cOne() { return one; }
	static Vector3 cRight() { return right; }
	static Vector3 cUp() { return up; }
	static Vector3 cZero() { return zero; }
	static Vector3 cInfinity() { return infinity; }

	float operator|(const Vector3 &rhs) const { return Vector3::dot(*this, rhs); }
	Vector3 operator^(const Vector3 &rhs) const { return Vector3::cross(*this, rhs); }

	bool operator!=(const Vector3 &other) const;

	Vector3 operator+=(const Vector3 &other) { return *this = *this + other; }
	Vector3 operator-=(const Vector3 &other) { return *this = *this - other; }
	Vector3 operator*=(const Vector3 &other) { return *this = *this * other; }
	Vector3 operator/=(const Vector3 &other) { return *this = *this / other; }

	Vector3 operator*=(float scale) { return *this = *this * scale; }
	Vector3 operator/=(float scale) { return *this = *this / scale; }

	explicit operator const float *() const { return &x; }
	explicit operator float *() { return &x; }

	const float *toPointer() const { return &x; }
	float *toPointer() { return &x; }

public:
	float x, y, z;

	static const Vector3 back;		//	Shorthand for writing Vector3(0, 0, -1).
	static const Vector3 down;		//	Shorthand for writing Vector3(0, -1, 0).
	static const Vector3 forward;	//	Shorthand for writing Vector3(0, 0, 1).
	static const Vector3 left;		//	Shorthand for writing Vector3(-1, 0, 0).
	static const Vector3 one;		//	Shorthand for writing Vector3(1, 1, 1).
	static const Vector3 right;		//	Shorthand for writing Vector3(1, 0, 0).
	static const Vector3 up;		//	Shorthand for writing Vector3(0, 1, 0).
	static const Vector3 zero;		//	Shorthand for writing Vector3(0, 0, 0).
	static const Vector3 infinity;  //  Shorthand for writing Vector3(FLT_MAX, FLT_MAX, FLT_MAX).
};


