#pragma once

struct Vector2;

struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
	Vector2 XZ() const;
	static Vector3 FromVector2(const Vector2 &val);
};


