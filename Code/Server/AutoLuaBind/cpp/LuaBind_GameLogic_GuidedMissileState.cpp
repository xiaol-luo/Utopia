#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "GameLogic/Scene/Missile/SceneUnitGuidedMissile/SceneUnitGuidedMissile.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_GuidedMissileState(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "GuidedMissileState";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"GuidedMissileState_None", 0,
					"GuidedMissileState_Ready", 1,
					"GuidedMissileState_Moving", 2,
					"GuidedMissileState_Hit", 3,
					"GuidedMissileState_Done", 4,
					"GuidedMissileState_Destroy", 5,
					"GuidedMissileState_AllFinish", 6
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}