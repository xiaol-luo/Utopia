#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "Logic/ShareCode/Network/Protobuf/Battle.pb.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneView/SceneView.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"

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