#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Network/Protobuf/Battle.pb.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/SceneView.h"

namespace SolLuaBind
{
	void LuaBind_NetProto(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "NetProto";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}