#pragma once

#include <sol.hpp>
#include <vector>
#include <string>

extern std::vector<std::function<void(lua_State *)>> LUA_BIND_USER_TYPE_FNS;

namespace TryUserType
{
	void AddLuaBindUserTypeFn(std::function<void(lua_State *)> fn);
	void ExecuteLuaBindUserTypeFns(lua_State *L);

	std::vector<std::string> PraseNameSpace(std::string ns);
}



