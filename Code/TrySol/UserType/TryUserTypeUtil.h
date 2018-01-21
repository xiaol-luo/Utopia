#pragma once

#include <sol.hpp>
#include <vector>
#include <string>

extern std::vector<std::function<void(lua_State *)>> LUA_BIND_USER_TYPE_FNS;

namespace TryUserType
{
	void AddLuaBindUserTypeFn(std::function<void(lua_State *)> fn);
	void ExecuteLuaBindUserTypeFns(lua_State *L);

	bool GetLuaTable(sol::state_view &lua, const std::vector<std::string> &table_names, 
		sol::table &out_obj, bool new_when_miss);
	std::vector<std::string> PraseNameSpace(std::string ns);
	sol::table GetOrNewLuaNameSpaceTable(sol::state_view &lua, const std::string &ns);
	
	template <typename T>
	void BindLuaUserType(sol::state_view &lua, sol::usertype<T> &meta_table, 
		const std::string &name, const std::string &ns)
	{
		sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, ns);
		ns_table.set_usertype(name, meta_table);
	}
}



