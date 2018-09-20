#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitBullet/Bullet.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EBulletTarget(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EBulletTarget";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EBulletTarget_Pos", 0,
					"EBulletTarget_SceneUnit", 1
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}