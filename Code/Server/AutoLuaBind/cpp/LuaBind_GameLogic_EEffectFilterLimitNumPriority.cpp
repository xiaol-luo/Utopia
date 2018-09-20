#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EEffectFilterLimitNumPriority(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EEffectFilterLimitNumPriority";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EEffectFilterLimitNumPriority_None", 0,
					"EEffectFilterLimitNumPriority_NearCaster", 1,
					"EEffectFilterLimitNumPriority_AwayCaster", 2,
					"EEffectFilterLimitNumPriority_NearTarget", 3,
					"EEffectFilterLimitNumPriority_AwayTarget", 4
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}