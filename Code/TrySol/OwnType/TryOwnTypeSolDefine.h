#pragma once

#include "TryOwnType.h"
#include <sol.hpp>

namespace sol
{
	template<>
	struct lua_size<TryOwnType::Head> : std::integral_constant<int, 2> {};

	template <>
	struct lua_type_of<TryOwnType::Head> : std::integral_constant<sol::type, sol::type::poly> {};

	namespace stack
	{
		template<>
		struct checker<TryOwnType::Head> 
		{
			template <typename Handler>
			static bool check(lua_State *L, int index, Handler &&handler, record &tracking)
			{
				int top = lua_absindex(L, -1);
				int abs_index = lua_absindex(L, index);
				int begin_idx = abs_index;
				bool is_ok = true;
				is_ok &= stack::check<float>(L, abs_index++, handler);
				is_ok &= stack::check<int>(L, abs_index++, handler);
				tracking.use(abs_index - begin_idx);
				return is_ok;
			}
		};

		template <>
		struct getter<TryOwnType::Head>
		{
			static TryOwnType::Head get(lua_State *L, int index, record& tracking)
			{
				int abs_index = lua_absindex(L, index);
				int begin_idx = abs_index;

				TryOwnType::Head ret 
				{ 
					stack::get<float>(L, abs_index++), 
					stack::get<int>(L, abs_index++) 
				};
				tracking.use(abs_index - begin_idx);
				return ret;
			}
		};

		template <>
		struct pusher<TryOwnType::Head>
		{
			static int push(lua_State *L, const TryOwnType::Head &things)
			{
				int amount = 0;
				amount += stack::push(L, things.weight);
				amount += stack::push(L, things.param_int);
				return amount;
			}
		};
	}
}

namespace sol
{
	template<>
	struct lua_size<TryOwnType::Human> : std::integral_constant<int, 1 + lua_size<TryOwnType::Head>::value> {};

	template <>
	struct lua_type_of<TryOwnType::Human> : std::integral_constant<sol::type, sol::type::poly> {};

	namespace stack
	{
		template<>
		struct checker<TryOwnType::Human>
		{
			template <typename Handler>
			static bool check(lua_State *L, int index, Handler &&handler, record &tracking)
			{
				int top = lua_absindex(L, -1);
				int abs_index = lua_absindex(L, index);
				int begin_idx = abs_index;
				bool is_ok = true;
				is_ok &= stack::check<std::string>(L, abs_index++, handler);
				is_ok &= stack::check<TryOwnType::Head>(L, abs_index++, handler);
				tracking.use(abs_index - begin_idx);
				return is_ok;
			}
		};

		template <>
		struct getter<TryOwnType::Human>
		{
			static TryOwnType::Human get(lua_State *L, int index, record& tracking)
			{
				int abs_index = lua_absindex(L, index);
				int begin_idx = abs_index;

				TryOwnType::Human ret
				{
					stack::get<std::string>(L, abs_index++),
					stack::get<TryOwnType::Head>(L, abs_index++)
				};
				tracking.use(abs_index - begin_idx);
				return ret;
			}
		};

		template <>
		struct pusher<TryOwnType::Human>
		{
			static int push(lua_State *L, const TryOwnType::Human &things)
			{
				int amount = 0;
				amount += stack::push(L, things.name);
				amount += stack::push(L, things.head);
				return amount;
			}
		};
	}
}

