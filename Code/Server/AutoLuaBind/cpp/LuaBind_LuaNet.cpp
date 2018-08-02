#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LuaHelps/LuaNet.h"

namespace SolLuaBind
{
	void LuaBind_LuaNet(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "LuaNet";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "SendBuffer";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, LuaNet::SendBuffer);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}