#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EEffectFilterShape(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EEffectFilterShape";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EffectFilterShape_None", 0,
					"EEffectFilterShape_Circle", 1,
					"EEffectFilterShape_Rect", 2,
					"EEffectFilterShape_Sector", 3
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}