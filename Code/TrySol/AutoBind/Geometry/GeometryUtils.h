#pragma once

#include <stdint.h>
#include "GeometryDefine.h"
#include <float.h>
#include <cstddef>

struct Vector2;
struct Vector3;

namespace GeometryUtils
{
	// 使用左手坐标系，顺时针为旋转正方向，2d 3d都以unity 3d的SignAngle函数的结果为标准
	float DeltaAngle(const Vector3 &from, const Vector3 & to);
	float DeltaAngle(const Vector2 &from, const Vector2 &to);
};


