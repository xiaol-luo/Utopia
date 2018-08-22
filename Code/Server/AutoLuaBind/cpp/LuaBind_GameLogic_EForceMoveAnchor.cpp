#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EForceMoveAnchor(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "EForceMoveAnchor";
				std::string name_space = "GameLogic";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"EForceMoveAnchor_Caster", 0,
					"EForceMoveAnchor_CastPos", 1,
					"EForceMoveAnchor_TargetPos", 2,
					"EForceMoveAnchor_TargetUnit", 3,
					"EForceMoveAnchor_EffectTargetUnit", 4,
					"EForceMoveAnchor_EffectTargetPos", 5,
					"EForceMoveAnchor_EffectDir", 6,
					"EForceMoveAnchor_SkillDir", 7,
					"EForceMoveAnchor_CastFaceDir", 8
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}