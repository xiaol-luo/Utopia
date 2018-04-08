#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Utils/AutoReleaseUtil.h"

namespace SolLuaBind
{
	void LuaBind_AutoReleaseUtil(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "AutoReleaseUtil";
				std::string name_space = "";

				{
					sol::usertype<AutoReleaseUtil> meta_table(
						sol::constructors<				
						AutoReleaseUtil()
						>(),
					"__StructName__", sol::property([]() {return "AutoReleaseUtil"; })				
						,"m_ptrs", &AutoReleaseUtil::m_ptrs
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