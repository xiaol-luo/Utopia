#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "AutoBind/Test/fake2.h"

namespace SolLuaBind
{
	void LuaBind_NS_UnknownItem(lua_State *L)
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
                std::string name = "UnknownItem";
				std::string name_space = "NS";

				{
					sol::usertype<NS::UnknownItem> meta_table(
						"__StructName__", sol::property([]() {return "UnknownItem"; })
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