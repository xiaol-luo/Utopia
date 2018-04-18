#pragma once

#include <sol.hpp>
#include <vector>
#include <string>

namespace SolLuaBindUtils
{
	bool GetLuaTable(sol::state_view &lua, const std::vector<std::string> &table_names, sol::table &out_obj, bool new_when_miss);
	std::vector<std::string> ParseNameSpace(std::string ns);
	sol::table GetOrNewLuaNameSpaceTable(sol::state_view &lua, const std::string &ns);
	sol::table GetLuaNameSpaceTable(sol::state_view &lua, const std::string &ns);

	template <typename T>
	void BindLuaUserType(sol::state_view &lua, sol::usertype<T> &meta_table, const std::string &name, const std::string &ns)
	{
		sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, ns);
		sol::object tb_obj = ns_table.raw_get_or(name, sol::nil);
		assert(!tb_obj.valid());
		ns_table.set_usertype(name, meta_table);
	}
}



