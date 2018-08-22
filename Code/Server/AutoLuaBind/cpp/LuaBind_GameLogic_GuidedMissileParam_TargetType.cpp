#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Missile/SceneUnitGuidedMissile/SceneUnitGuidedMissile.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_GuidedMissileParam_TargetType(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "TargetType";
				std::string name_space = "GameLogic.GuidedMissileParam";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"TargetType_Pos", 0,
					"TargetType_SceneUnit", 1
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}