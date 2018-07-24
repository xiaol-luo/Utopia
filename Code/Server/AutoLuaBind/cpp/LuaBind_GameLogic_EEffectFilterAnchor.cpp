#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EEffectFilterAnchor(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EEffectFilterAnchor";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EEffectFilterAnchor_Caster", 0,
					"EEffectFilterAnchor_CastPos", 1,
					"EEffectFilterAnchor_TargetPos", 2,
					"EEffectFilterAnchor_TargetUnit", 3,
					"EEffectFilterAnchor_EffectTargetUnit", 4,
					"EEffectFilterAnchor_EffectTargetPos", 5
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}