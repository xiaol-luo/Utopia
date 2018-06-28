#include "LuaUtils.h"
#include "lrdb/server.hpp"

namespace LuaUtils
{
	lua_State *luaState = nullptr;

	int LuaPanicFn(lua_State *l)
	{
		return 0;
	}

	lrdb::server *lrdb_debug_srv = nullptr;

	void Init()
	{
		Uninit();
		luaState = luaL_newstate();
		{
			const int LRDB_LISTEN_PORT = 21110;
			lrdb_debug_srv = new lrdb::server(LRDB_LISTEN_PORT);
			lrdb_debug_srv->reset(LuaUtils::luaState);
		}
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
			, sol::lib::package
		);
	}
	void Uninit()
	{
		if (nullptr != lrdb_debug_srv)
		{
			lrdb_debug_srv->reset();
			delete lrdb_debug_srv;
			lrdb_debug_srv = nullptr;
		}
		if (nullptr != luaState)
		{
			lua_close(luaState);
			luaState = nullptr;
		}
	}

	lua_State * GetState()
	{
		return luaState; 
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