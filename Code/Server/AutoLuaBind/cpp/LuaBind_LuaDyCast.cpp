#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LuaHelps/LuaDynamicCasts.h"	
#include "GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace SolLuaBind
{
	void LuaBind_LuaDyCast(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "LuaDyCast";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "ToEffectScriptConfig";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, LuaDyCast::ToEffectScriptConfig);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}