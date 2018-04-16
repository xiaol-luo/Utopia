#pragma once

#include <sol.hpp>

namespace LuaUtils
{
	extern lua_State *luaState;
	void Init();
	void Uninit();
	sol::protected_function ProtectFnErrorHandler();
	sol::protected_function_result ErrorFn(lua_State *L, sol::protected_function_result pfr);
}

