#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "ShareCode/Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneUnitFilterWayParams(lua_State *L)
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
                std::string name = "ESceneUnitFilterWayParams";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::ESceneUnitFilterWayParams> meta_table(
						sol::constructors<				
						GameLogic::ESceneUnitFilterWayParams()
						>(),
						"__StructName__", sol::property([]() {return "ESceneUnitFilterWayParams"; })				
						,"is_active", &GameLogic::ESceneUnitFilterWayParams::is_active				
						,"exclude_suids", &GameLogic::ESceneUnitFilterWayParams::exclude_suids				
						,"relations", &GameLogic::ESceneUnitFilterWayParams::relations				
						,"shape_obb2", &GameLogic::ESceneUnitFilterWayParams::shape_obb2				
						,"shape_circle", &GameLogic::ESceneUnitFilterWayParams::shape_circle				
						,"shape_sector", &GameLogic::ESceneUnitFilterWayParams::shape_sector				
						,"limit_num", &GameLogic::ESceneUnitFilterWayParams::limit_num				
						,"unit_type", &GameLogic::ESceneUnitFilterWayParams::unit_type
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