
#include "Vector3.h"
#include "Vector2.h"
#include "GeometryUtils.h"
#include <math.h>
#include <cfloat>

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

Vector3 Vector3::operator+(const Vector3 &other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3 Vector3::operator-(const Vector3 &other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}
Vector3 Vector3::operator*(const Vector3 &other) const
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}
Vector3 Vector3::operator/(float scale) const
{
	if (scale < FLT_EPSILON)
		return *this;
	return Vector3(x/scale, y/scale, z/scale);
}
Vector3 Vector3::operator*(float scale) const
{
	return Vector3(x*scale, y*scale, z*scale);
}
Vector3 Vector3::operator/(const Vector3 &other) const
{
	return Vector3(x / other.x, y / other.y, z / other.z);
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
	return !((*this) == other);
}

float Vector3::magnitude() const
{
	return sqrtf(sqrMagnitude());
}

void Vector3::normalize()
{
	float mag = magnitude();
	if (mag <= FLT_EPSILON)
		return;

	x /= mag, y /= mag, z /= mag;
}

Vector3 Vector3::normalized() const
{
	Vector3 temp = *this;
	temp.normalize();
	return temp;
}

float Vector3::sqrMagnitude() const
{
	return x*x + y*y + z*z;
}

void Vector3::set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

Vector2 Vector3::xz() const
{
	return Vector2(x, z);
}

Vector3 Vector3::cross(const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}

float Vector3::dot(const Vector3 &lhs, const Vector3 &rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::moveTowards(const Vector3 &lhs, const Vector3 &rhs, float clampedDistance)
{
	Vector3 delta = rhs - lhs;
	float sqrDelta = delta.sqrMagnitude();
	float sqrClampedDistance = clampedDistance * clampedDistance;
	if (sqrDelta > sqrClampedDistance) {
		float deltaMag = sqrt(sqrDelta);
		if (deltaMag > FLT_EPSILON)
			return lhs + delta / deltaMag * clampedDistance;
		else
			return lhs;
	} else
		return rhs;
}

