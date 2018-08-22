#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Effects/EffectForceMove/EffectForceMoveConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectForceMoveConfig_MoveSetting(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "MoveSetting";
				std::string name_space = "GameLogic.EffectForceMoveConfig";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"TimeSpeed", 0,
					"TimeDistance", 1,
					"DistanceSpeed", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}