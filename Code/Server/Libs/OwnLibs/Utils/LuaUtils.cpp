#include "LuaUtils.h"

namespace LuaUtils
{
	lua_State *luaState = nullptr;

	int LuaPanicFn(lua_State *l)
	{
		return 0;
	}

	void Init()
	{
		Uninit();
		luaState = luaL_newstate();
		sol::state_view luaSv(luaState);
		luaSv.set_panic(LuaPanicFn);
		luaSv.script(R"(
			function ___DefaultErrorHandler(msg) 
				local out_msg = "Lua Error Handler" .. msg 
				print(out_msg)
				return out_msg
			end 
		)");

		luaSv.open_libraries(
			sol::lib::debug
			, sol::lib::base
			, sol::lib::coroutine
			, sol::lib::string
			, sol::lib::os
			, sol::lib::math
			, sol::lib::table
			, sol::lib::bit32
			, sol::lib::io
			, sol::lib::utf8
		);
	}
	void Uninit()
	{
		if (nullptr != luaState)
		{
			lua_close(luaState);
			luaState = nullptr;
		}
	}

	sol::protected_function ProtectFnErrorHandler()
	{
		sol::state_view lsv(luaState);
		sol::protected_function ret = lsv["___DefaultErrorHandler"];
		return ret;
	}

	sol::protected_function_result ErrorFn(lua_State *L, sol::protected_function_result pfr)
	{
		sol::error err = pfr;
		printf("LuaErrorProtectedFn %s\n", err.what());
		return pfr;
	}
}