#pragma once

struct Vector2
{
	float x = 0.0f, y = 0.0f;

	template <typename X>
	void test(X x) {}
};

template <typename X>
class TestTemplate
{

};
