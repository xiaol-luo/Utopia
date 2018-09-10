#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Geometry/GeometryDefine.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "ShareCode/Common/Geometry/Vector3.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitFilterWayParams(lua_State *L)
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
                std::string name = "SceneUnitFilterWayParams";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitFilterWayParams> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitFilterWayParams()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitFilterWayParams"; })				
						,"is_active", &GameLogic::SceneUnitFilterWayParams::is_active				
						,"shape", &GameLogic::SceneUnitFilterWayParams::shape				
						,"cached_shape_aabb", &GameLogic::SceneUnitFilterWayParams::cached_shape_aabb				
						,"exclude_suids", &GameLogic::SceneUnitFilterWayParams::exclude_suids				
						,"relations", &GameLogic::SceneUnitFilterWayParams::relations				
						,"shape_obb2", &GameLogic::SceneUnitFilterWayParams::shape_obb2				
						,"shape_circle", &GameLogic::SceneUnitFilterWayParams::shape_circle				
						,"shape_sector", &GameLogic::SceneUnitFilterWayParams::shape_sector				
						,"limit_num", &GameLogic::SceneUnitFilterWayParams::limit_num				
						,"unit_type", &GameLogic::SceneUnitFilterWayParams::unit_type				
						,"CalShape", &GameLogic::SceneUnitFilterWayParams::CalShape
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