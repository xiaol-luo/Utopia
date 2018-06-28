#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Network/Protobuf/Battle.pb.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"	
#include "GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"	
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"

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