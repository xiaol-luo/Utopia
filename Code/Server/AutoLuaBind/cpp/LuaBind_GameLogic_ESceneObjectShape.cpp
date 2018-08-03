#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "GameLogic/Scene/Defines/SceneDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneObjectShape(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ESceneObjectShape";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ESceneObjectShape_Circle", 0,
					"ESceneObjectShape_Rect", 1
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}