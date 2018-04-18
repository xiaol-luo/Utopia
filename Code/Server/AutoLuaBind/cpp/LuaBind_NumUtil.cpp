#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Utils/NumUtils.h"

namespace SolLuaBind
{
	void LuaBind_NumUtil(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "NumUtil";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "BIT_PER_BYTE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, NumUtil::BIT_PER_BYTE);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}