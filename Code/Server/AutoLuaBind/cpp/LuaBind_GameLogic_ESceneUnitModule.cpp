#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Defines/SceneDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneUnitModule(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ESceneUnitModule";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ESceneUnitModule_Transform", 0,
					"ESceneUnitModule_FightParam", 1,
					"ESceneUnitModule_Move", 2,
					"ESceneUnitModule_Body", 3,
					"ESceneUnitModule_Sight", 4,
					"ESceneUnitModule_Action", 5,
					"ESceneUnitModule_Skills", 6,
					"ESceneUnitModule_Missle", 7,
					"ESceneUnitModule_Count", 8
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}