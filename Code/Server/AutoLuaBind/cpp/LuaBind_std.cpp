#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/Vector2.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "LogicModules/GameLogic/Scene/Defines/ViewDefine.h"

namespace SolLuaBind
{
	void LuaBind_std(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "std";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}