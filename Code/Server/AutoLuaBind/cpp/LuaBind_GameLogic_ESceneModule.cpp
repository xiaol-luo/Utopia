#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/SceneDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneModule(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ESceneModule";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ESceneModule_NavMesh", 0,
					"ESceneModule_Move", 1,
					"ESceneModule_View", 2,
					"ESceneModule_Effects", 3,
					"ESceneModule_UnitFilter", 4,
					"ESceneModule_Count", 5
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}