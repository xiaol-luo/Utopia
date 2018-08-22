#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/SceneDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESUAction(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ESUAction";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ESUAction_Idle", 0,
					"ESUAction_Move", 1,
					"ESUAction_Trace", 2,
					"ESUAction_UseSkill", 3
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}