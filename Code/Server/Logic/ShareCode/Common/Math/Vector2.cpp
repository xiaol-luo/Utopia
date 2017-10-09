
#include "Vector2.h"
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
	assert(i >= 0 && i <= 1); 
	return (&x)[i]; 
}

Vector2 Vector2::operator + (const Vector2& inV) 
{
	return Vector2(x+inV.x, y+inV.y); 
}

Vector2 Vector2::operator - (const Vector2& inV) 
{ 
	return Vector2(x-inV.x, y-inV.y); 
}

Vector2 Vector2::operator * (const float s) 
{ 
	return Vector2(x*s, y*s); 
}

Vector2 Vector2::operator / (float s) 
{
	assert(s < 1e-5);	
	return Vector2(x/s, y/s); 
}

bool Vector2::operator == (const Vector2& v)const 
{ 
	return x == v.x && y == v.y; 
}

bool Vector2::operator != (const Vector2& v)const 
{ 
	return x != v.x || y != v.y; 
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

Vector2 Vector2::scale(const Vector2& inV) 
{ 
	x *= inV.x; y *= inV.y; 
	return *this; 
}

float Vector2::dot(const Vector2 &lhs, const Vector2 &rhs) 
{ 
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::sqrMagnitude() 
{ 
	return x*x + y*y; 
}

float Vector2::magnitude() 
{ 
	return sqrtf(sqrMagnitude()); 
}

void Vector2::normalize() 
{ 
	float mag = magnitude();
	if (mag <= FLT_EPSILON)
		return;
	x /= mag; y /= mag;
}

void Vector2::set(float inX, float inY) 
{ 
	x = inX; y = inY; 
}

Vector2 Vector2::inverse() 
{ 
	return Vector2(1.0F / x, 1.0F / y);
}

float Vector2::angle(Vector2 &rhs) 
{ 
	return acos(std::min(1.0f, std::max(-1.0f, (*this|rhs) / (magnitude() * rhs.magnitude())))); 
}

Vector2 Vector2::rotate(float radian)
{
	return Vector2(x * cos(radian) - y * sin(radian), y * cos(radian) + x * sin(radian));
}
