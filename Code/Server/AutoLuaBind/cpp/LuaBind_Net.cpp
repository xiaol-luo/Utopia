#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Define/NetworkDefine.h"

namespace SolLuaBind
{
	void LuaBind_Net(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "Net";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "PROTOCOL_LEN_DESCRIPT_SIZE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, Net::PROTOCOL_LEN_DESCRIPT_SIZE);
				}				
				{
					std::string name = "PROTOCOL_CONTENT_MAX_SIZE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, Net::PROTOCOL_CONTENT_MAX_SIZE);
				}				
				{
					std::string name = "PROTOCOL_MAX_SIZE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, Net::PROTOCOL_MAX_SIZE);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}