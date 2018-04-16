
#include "Vector3.h"
#include "Vector2.h"
#include "GeometryUtils.h"
#include <cfloat>
#include <memory>
#include <algorithm>

Vector2 Vector3::XZ() const
{
	return std::move(Vector2());
}

Vector3 Vector3::FromVector2(const Vector2 & val)
{
	return Vector3(); 
}

