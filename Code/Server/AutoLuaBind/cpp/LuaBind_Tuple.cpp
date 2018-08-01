#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Utils/TupleUtil.h"

namespace SolLuaBind
{
	void LuaBind_Tuple(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "Tuple";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}