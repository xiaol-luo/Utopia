#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_obb2(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "_shape_obb2";
				std::string name_space = "GameLogic.ESceneUnitFilterWayParams";

				{
					sol::usertype<GameLogic::ESceneUnitFilterWayParams::_shape_obb2> meta_table(
						"__StructName__", sol::property([]() {return "_shape_obb2"; })				
						,"oob2", &GameLogic::ESceneUnitFilterWayParams::_shape_obb2::oob2
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}