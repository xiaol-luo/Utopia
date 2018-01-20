#include "TryUserTypeUtil.h"

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

std::vector<std::string> TryUserType::PraseNameSpace(std::string ns)
{
	std::vector<std::string> ret;

	auto last_it = ns.begin();
	for (auto it = ns.begin(); it != ns.end(); ++it)
	{
		char c = *it;
		if (!std::isalpha(c) && '.' != c)
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
