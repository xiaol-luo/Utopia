
#include "Vector2.h"
#include "Vector3.h"
#include <cassert>
#include <algorithm>
#include <math.h>
#include <float.h>

using namespace std;

const Vector2 Vector2::infinity = Vector2(numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
const Vector2 Vector2::zero = Vector2(0, 0);
const Vector2 Vector2::one = Vector2(1, 1);
const Vector2 Vector2::left = Vector2(-1, 0);
const Vector2 Vector2::right = Vector2(1, 0);
const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::down = Vector2(0, -1);

float Vector2::operator[] (int i)
{ 
	assert(i >= 0 && i < 2); 
	return (&x)[i]; 
}

Vector2 Vector2::operator + (const Vector2& inV) const
{
	return Vector2(x+inV.x, y+inV.y); 
}

Vector2 Vector2::operator - (const Vector2& inV) const
{ 
	return Vector2(x-inV.x, y-inV.y); 
}

Vector2 Vector2::operator * (const float s) const
{ 
	return Vector2(x*s, y*s); 
}

Vector2 Vector2::operator / (float s) const
{
	assert(std::abs(s) > FLT_EPSILON);	
	return Vector2(x/s, y/s); 
}

bool Vector2::operator == (const Vector2& v)const 
{ 
	return x == v.x && y == v.y; 
}

bool Vector2::operator != (const Vector2& v)const 
{ 
	return !(this->operator ==(v));
}

Vector2 Vector2::operator -() const 
{ 
	return Vector2(-x, -y); 
}

Vector2::operator const float *() const 
{ 
	return &x; 
}

Vector2::operator float *() 
{ 
	return &x; 
}

void Vector2::Scale(float scale) 
{ 
	x *= scale; y *= scale; 
}

float Vector2::Dot(const Vector2 &lhs, const Vector2 &rhs) 
{ 
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::Cross(const Vector2 & lhs, const Vector2 & rhs)
{
	Vector3 l = Vector3(lhs.x, 0, lhs.y);
	Vector3 r = Vector3(rhs.x, 0, rhs.y);
	Vector3 ret = Vector3::Cross(l, r);
	return ret.XZ();
}

Vector2 Vector2::Normalize(const Vector2 & val)
{
	Vector2 ret = val;
	ret.Normalize();
	return std::move(ret);
}

Vector2 Vector2::Scale(const Vector2 & val, float scale)
{
	Vector2 ret = val;
	ret.Scale(scale);
	return std::move(ret);
}

Vector2 Vector2::Inverse(const Vector2 & val)
{
	Vector2 ret = val;
	ret.Inverse();
	return ret;
}

float Vector2::SqrMagnitude() const
{ 
	return x*x + y*y; 
}

float Vector2::Magnitude() const
{ 
	return sqrtf(SqrMagnitude()); 
}

void Vector2::Normalize() 
{ 
	float mag = Magnitude();
	if (mag <= FLT_EPSILON)
		return;
	x /= mag; y /= mag;
}

void Vector2::Set(float inX, float inY) 
{ 
	x = inX; y = inY; 
}

void Vector2::Inverse() 
{ 
	if (std::abs(x) >= FLT_EPSILON)
		x = 1.0f / x;
	if (std::abs(y) >= FLT_EPSILON)
		y = 1.0f / y;
}

