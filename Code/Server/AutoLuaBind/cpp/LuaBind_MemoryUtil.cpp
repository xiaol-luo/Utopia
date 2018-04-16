#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Libs/3rdpartLibs/protobuf/include/google/protobuf/arena.h"	
#include "Libs/OwnLibs/MemoryPool/MemoryPoolMgr.h"	
#include "Logic/ShareCode/Common/Utils/MemoryUtil.h"

namespace SolLuaBind
{
	void LuaBind_MemoryUtil(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = MemoryPoolMgr *;
				using TypeAlias_2 = bool;
				static TypeAlias_2 Init1(TypeAlias_1 p1)
				{
					return MemoryUtil::Init(p1);
				}
				using TypeAlias_3 = bool;
				static TypeAlias_3 Init2()
				{
					return MemoryUtil::Init();
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "MemoryUtil";
				std::string name_space = "";

				{
					sol::usertype<MemoryUtil> meta_table(
						"__StructName__", sol::property([]() {return "MemoryUtil"; })				
						,"Destroy", &MemoryUtil::Destroy				
						,"Malloc", &MemoryUtil::Malloc				
						,"Free", &MemoryUtil::Free				
						,"Realloc", &MemoryUtil::Realloc				
						,"NewArena", &MemoryUtil::NewArena				
						,"Init", sol::overload(ForOverloadFns::Init1, ForOverloadFns::Init2)
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