#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EEffectFilterRelation(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EEffectFilterRelation";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EEffectFilterRelation_Self", 0,
					"EEffectFilterRelation_Friend", 1,
					"EEffectFilterRelation_Enemy", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}