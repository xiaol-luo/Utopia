#include "TryUserTypeUtil.h"
#include "TryUserType.h"

std::vector<std::function<void(lua_State *)>> LUA_BIND_USER_TYPE_FNS;

void TryUserType::AddLuaBindUserTypeFn(std::function<void(lua_State *)> fn)
{
	if (nullptr == fn)
		return;
	LUA_BIND_USER_TYPE_FNS.push_back(fn);
}

void TryUserType::ExecuteLuaBindUserTypeFns(lua_State * L)
{
	for (auto fn : LUA_BIND_USER_TYPE_FNS)
	{
		fn(L);
	}
	LUA_BIND_USER_TYPE_FNS.clear();
}


bool TryUserType::GetLuaTable(sol::state_view &lua, const std::vector<std::string> &table_names,
	sol::table &out_obj, bool new_when_miss)
{
	bool ret = true;
	sol::table curr_table = lua.globals();
	for (size_t i = 0; i < table_names.size(); ++i)
	{
		const std::string &table_name = table_names[i];
		sol::optional<sol::object> opt_object = curr_table[table_name];
		if (!opt_object)
		{
			if (!new_when_miss)
			{
				ret = false;
				break;
			}
			curr_table = curr_table.create_named(table_name);
		}
		else
		{
			if (!opt_object.value().is<sol::table>())
			{
				if (new_when_miss)
					assert(false);
				ret = false;
				break;
			}
			curr_table = opt_object.value().as<sol::table>();
		}
	}

	out_obj = curr_table;
	return ret;
}

std::vector<std::string> TryUserType::PraseNameSpace(std::string ns)
{
	std::vector<std::string> ret;

	auto last_it = ns.begin();
	for (auto it = ns.begin(); it != ns.end(); ++it)
	{
		char c = *it;
		if (!std::isalpha(c) && '.' != c && '_' != c)
		{
			assert(false);
		}

		if ('.' == c)
		{
			std::string new_str(last_it, it);
			if (!new_str.empty())
				ret.push_back(new_str);
			last_it = it + 1;
		}
	}
	if (last_it != ns.end())
	{
		std::string new_str(last_it, ns.end());
		if (!new_str.empty())
			ret.push_back(new_str);
	}

	return std::move(ret);
}

sol::table TryUserType::GetOrNewLuaNameSpaceTable(sol::state_view &lua, const std::string & ns)
{
	std::vector<std::string> ns_vec = PraseNameSpace(ns);
	sol::table out_table;
	if (!TryUserType::GetLuaTable(lua, ns_vec, out_table, true))
		assert(false);
	return out_table;
}
