#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Utils/MemoryUtil.h"

namespace SolLuaBind
{
	void LuaBind_MemoryUtil(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				static bool Init1(MemoryPoolMgr * p1)
				{
					return MemoryUtil::Init(p1);
				}
				static bool Init2()
				{
					return MemoryUtil::Init();
				}
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