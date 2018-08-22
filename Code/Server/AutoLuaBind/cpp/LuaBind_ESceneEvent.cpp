#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "LogicModules/GameLogic/Scene/Defines/ESceneEvent.h"

namespace SolLuaBind
{
	void LuaBind_ESceneEvent(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "ESceneEvent";
				std::string name_space = "";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"ESU_PosChange", 0,
					"ESU_EnterScene", 1,
					"ESU_LeaveScene", 2,
					"ESU_VolecityChange", 3,
					"ESU_MoveStateChange", 4,
					"ESU_FightParamChange", 5,
					"ESU_DizzinessChange", 6,
					"ESU_ImmobilizedChange", 7,
					"ESU_BlindChange", 8,
					"ESU_SilenceChange", 9,
					"ESU_DeadChange", 10,
					"ESU_HpChange", 11,
					"ESU_MpChange", 12,
					"ES_ReloadConfig", 13,
					"ES_TestHeartBeat", 14
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}