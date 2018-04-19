#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_EventDispacher(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "EventDispacher";
				std::string name_space = "";

				{
					sol::usertype<EventDispacher> meta_table(
						sol::constructors<				
						EventDispacher()
						>(),
						"__StructName__", sol::property([]() {return "EventDispacher"; })				
						,"Cancel", &EventDispacher::Cancel
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "INVALID_ID";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, EventDispacher::INVALID_ID);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}