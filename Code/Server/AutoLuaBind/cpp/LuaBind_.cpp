#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "google/protobuf/arena.h"	
#include "ShareCode/Common/Geometry/GeometryDefine.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "MemoryPool/MemoryPoolMgr.h"	
#include "ShareCode/Common/Utils/MemoryUtil.h"

namespace SolLuaBind
{
	void LuaBind_(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "KPi";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, KPi);
				}				
				{
					std::string name = "K2Pi";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, K2Pi);
				}				
				{
					std::string name = "KPiOver2";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, KPiOver2);
				}				
				{
					std::string name = "K1OverPi";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, K1OverPi);
				}				
				{
					std::string name = "K1Over2Pi";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, K1Over2Pi);
				}				
				{
					std::string name = "KPiOver180";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, KPiOver180);
				}				
				{
					std::string name = "K180OverPi";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, K180OverPi);
				}				
				{
					std::string name = "Malloc";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, Malloc);
				}				
				{
					std::string name = "Free";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, Free);
				}				
				{
					std::string name = "Realloc";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, Realloc);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}