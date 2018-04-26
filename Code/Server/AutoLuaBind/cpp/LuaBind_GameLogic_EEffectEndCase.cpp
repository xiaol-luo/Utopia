#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EEffectEndCase(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EEffectEndCase";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EEffectEndCase_Both", 0,
					"EEffectEndCase_Done", 1,
					"EEffectEndCase_Break", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}