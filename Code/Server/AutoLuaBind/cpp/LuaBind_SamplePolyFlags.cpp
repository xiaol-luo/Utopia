#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavMeshUtil.h"

namespace SolLuaBind
{
	void LuaBind_SamplePolyFlags(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "SamplePolyFlags";
				std::string name_space = "";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"SAMPLE_POLYFLAGS_WALK", 1,
					"SAMPLE_POLYFLAGS_SWIM", 2,
					"SAMPLE_POLYFLAGS_DOOR", 4,
					"SAMPLE_POLYFLAGS_JUMP", 8,
					"SAMPLE_POLYFLAGS_DISABLED", 16,
					"SAMPLE_POLYFLAGS_ALL", 65535
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}