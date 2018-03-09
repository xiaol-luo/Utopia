
#include "Vector3.h"
#include "Vector2.h"
#include "GeometryUtils.h"
#include <cfloat>
#include <memory>
#include <algorithm>

const Vector3 Vector3::back(0, 0, -1);		//	Shorthand for writing Vector3(0, 0, -1).
const Vector3 Vector3::down(0, -1, 0);		//	Shorthand for writing Vector3(0, -1, 0).
const Vector3 Vector3::forward(0, 0, 1);	//	Shorthand for writing Vector3(0, 0, 1).
const Vector3 Vector3::left(-1, 0, 0);		//	Shorthand for writing Vector3(-1, 0, 0).
const Vector3 Vector3::one(1, 1, 1);		//	Shorthand for writing Vector3(1, 1, 1).
const Vector3 Vector3::right(1, 0, 0);		//	Shorthand for writing Vector3(1, 0, 0).
const Vector3 Vector3::up(0, 1, 0);			//	Shorthand for writing Vector3(0, 1, 0).
const Vector3 Vector3::zero(0, 0, 0);		//	Shorthand for writing Vector3(0, 0, 0).
const Vector3 Vector3::infinity(FLT_MAX, FLT_MAX, FLT_MAX);//	Shorthand for writing Vector3(FLT_MAX, FLT_MAX, FLT_MAX).

float Vector3::operator[](int index) const
{
	return ((float*)this)[index];
}

void Vector3::operator=(const Vector3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3 Vector3::operator-(const Vector3 &other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator/(float scale) const
{
	if (std::abs(scale) < FLT_EPSILON)
		return *this;
	return Vector3(x/scale, y/scale, z/scale);
}
Vector3 Vector3::operator*(float scale) const
{
	return Vector3(x*scale, y*scale, z*scale);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3 &other) const
{
	return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3 &other) const
{
	// return !((*this) == other);
	return !(this->operator ==(other));
}

float Vector3::Magnitude() const
{
	return sqrtf(SqrMagnitude());
}

void Vector3::Normalize()
{
	float mag = Magnitude();
	if (mag <= FLT_EPSILON)
		return;

	x /= mag, y /= mag, z /= mag;
}

float Vector3::SqrMagnitude() const
{
	return x*x + y*y + z*z;
}

void Vector3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

void Vector3::Scale(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vector3::Inverse()
{
	if (std::abs(x) >= FLT_EPSILON)
		x = 1.0f / x;
	if (std::abs(y) >= FLT_EPSILON)
		y = 1.0f / y;
	if (std::abs(z) >= FLT_EPSILON)
		y = 1.0f / z;
}

Vector2 Vector3::XZ() const
{
	return std::move(Vector2(x, z));
}

Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}

float Vector3::Dot(const Vector3 &lhs, const Vector3 &rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Normalize(const Vector3 & val)
{
	Vector3 ret = val;
	ret.Normalize();
	return std::move(ret);
}

Vector3 Vector3::Scale(const Vector3 & val, float scale)
{

	Vector3 ret = val;
	ret.Scale(scale);
	return std::move(ret);
}

Vector3 Vector3::Inverse(const Vector3 & val)
{
	Vector3 ret = val;
	ret.Inverse();
	return std::move(ret);
}

Vector3 Vector3::FromVector2(const Vector2 & val)
{
	return Vector3(val.x, 0, val.y); 
}

