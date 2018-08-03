#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/EventDispatcher/EventDispacher.h"

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
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}