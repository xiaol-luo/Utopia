#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/GeometryDefine.h"	
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitBody(lua_State *L)
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
                std::string name = "SceneUnitBody";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitBody> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitBody()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitBody"; })				
						,"SetSceneView", &GameLogic::SceneUnitBody::SetSceneView				
						,"SetRadius", &GameLogic::SceneUnitBody::SetRadius				
						,"GetRadius", &GameLogic::SceneUnitBody::GetRadius				
						,"UpdateState", &GameLogic::SceneUnitBody::UpdateState				
						,"CovertRect", &GameLogic::SceneUnitBody::CovertRect				
						,"GetEShape", &GameLogic::SceneUnitBody::GetEShape				
						,"GetShapeObb2", &GameLogic::SceneUnitBody::GetShapeObb2				
						,"GetShapeCircle", &GameLogic::SceneUnitBody::GetShapeCircle				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitBody::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}