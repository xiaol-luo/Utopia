
#include <sol.hpp>
#include <lua.h>
#include <iostream>
#include <assert.h>
#include "OwnType/TryOwnTypeSolDefine.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("function f (a, b) print(a, b) return a, b end");
	sol::function f = lua["f"];
	TryOwnType::Head one_head;
	one_head.weight = 10.0f;
	one_head.param_int = 20;
	f(one_head);
	TryOwnType::Head another_head = f(one_head);
	printf("another_head { %f, %d } \n", another_head.weight, another_head.param_int);

	lua.script("function g (a, b, c) print(a, b) return a, b, c end");
	sol::function g = lua["g"];
	TryOwnType::Human one_human;
	one_human.name = "lxl";
	one_human.head = one_head;
	g(one_human);
	TryOwnType::Human anohter_human = g(one_human);
	printf("anohter_human {%s, %f, %d } \n", anohter_human.name.c_str(), anohter_human.head.weight, anohter_human.head.param_int);
}
