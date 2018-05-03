#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Utils/AutoReleaseUtil.h"

namespace SolLuaBind
{
	void LuaBind_IAutoReleaseObject(lua_State *L)
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
                std::string name = "IAutoReleaseObject";
				std::string name_space = "";

				{
					sol::usertype<IAutoReleaseObject> meta_table(
						sol::constructors<				
						IAutoReleaseObject()
						>(),
						"__StructName__", sol::property([]() {return "IAutoReleaseObject"; })				
						,"operator new", &IAutoReleaseObject::operator new				
						,"operator delete", &IAutoReleaseObject::operator delete				
						,"operator new[]", &IAutoReleaseObject::operator new[]				
						,"operator delete[]", &IAutoReleaseObject::operator delete[]
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