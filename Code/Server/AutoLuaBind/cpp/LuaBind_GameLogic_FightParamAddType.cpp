#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_FightParamAddType(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "FightParamAddType";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"FightParamAddType_Base", 0,
					"FightParamAddType_Extra", 1,
					"FightParamAddType_Percent", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}