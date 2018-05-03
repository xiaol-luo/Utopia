#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/ViewDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EViewCamp(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EViewCamp";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EViewCamp_Red", 0,
					"EViewCamp_Blue", 1,
					"EViewCamp_Monster", 2,
					"EViewCamp_Observer", 3,
					"EViewCamp_All", 4
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}