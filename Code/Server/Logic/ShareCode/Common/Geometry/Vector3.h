#pragma once

struct Vector2;

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vector3(const float *p) : x(p[0]), y(p[1]), z(p[2]) {}
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
	Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}

	float operator [] (int index) const;
	void operator = (const Vector3 &other);
	Vector3 operator + (const Vector3 &other) const;
	Vector3 operator - (const Vector3 &other) const;
	Vector3 operator * (float scale) const;
	Vector3 operator / (float scale) const;
	Vector3 operator - () const;
	bool operator == (const Vector3 &other) const;
	bool operator != (const Vector3 &other) const;

	operator const float *() const { return &x; }
	operator float *() { return &x; }
	const float * toPointer() const { return &x; }
	float * toPointer() { return &x; }
	Vector2 XZ() const;

	void Normalize();
	void Set(float x, float y, float z);
	void Scale(float scale);
	void Inverse();
	// the squared length of this vector
	float SqrMagnitude() const;
	// Returns the length of this vector
	float Magnitude() const;


	static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs);
	static float Dot(const Vector3 &lhs, const Vector3 &rhs);
	static Vector3 Normalize(const Vector3 &val);
	static Vector3 Scale(const Vector3 &val, float scale);
	static Vector3 Inverse(const Vector3 &val);
	static Vector3 FromVector2(const Vector2 &val);

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


