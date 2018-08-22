#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Missile/SceneUnitBullet/Bullet.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EBulletState(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EBulletState";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EBulletState_None", 0,
					"EBulletState_Ready", 1,
					"EBulletState_Moving", 2,
					"EBulletState_Done", 3,
					"EBulletState_Destroying", 4,
					"EBulletState_AllFinish", 5
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}