#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_EventDispacherProxy(lua_State *L)
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
                std::string name = "EventDispacherProxy";
				std::string name_space = "";

				{
					sol::usertype<EventDispacherProxy> meta_table(
						sol::constructors<				
						EventDispacherProxy(EventDispacher *)
						>(),
						"__StructName__", sol::property([]() {return "EventDispacherProxy"; })				
						,"Cancel", &EventDispacherProxy::Cancel				
						,"CancelAll", &EventDispacherProxy::CancelAll
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