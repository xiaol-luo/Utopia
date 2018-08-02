#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavMeshUtil.h"

namespace SolLuaBind
{
	void LuaBind_SamplePartitionType(lua_State *L)
	{
		struct LuaBindImpl
		{
			static void DoLuaBind(lua_State *L)
			{
				std::string name = "SamplePartitionType";
				std::string name_space = "";

				sol::state_view lua(L);
				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"SAMPLE_PARTITION_WATERSHED", 0,
					"SAMPLE_PARTITION_MONOTONE", 1,
					"SAMPLE_PARTITION_LAYERS", 2
				);
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}