#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavMeshUtil.h"

namespace SolLuaBind
{
	void LuaBind_SamplePolyAreas(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "SamplePolyAreas";
				std::string name_space = "";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"SAMPLE_POLYAREA_GROUND", 0,
					"SAMPLE_POLYAREA_WATER", 1,
					"SAMPLE_POLYAREA_ROAD", 2,
					"SAMPLE_POLYAREA_DOOR", 3,
					"SAMPLE_POLYAREA_GRASS", 4,
					"SAMPLE_POLYAREA_JUMP", 5
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}