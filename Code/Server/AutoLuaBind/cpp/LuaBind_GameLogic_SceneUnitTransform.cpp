#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitTransform(lua_State *L)
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
                std::string name = "SceneUnitTransform";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitTransform> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitTransform()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitTransform"; })				
						,"SetParent", &GameLogic::SceneUnitTransform::SetParent				
						,"AddChild", &GameLogic::SceneUnitTransform::AddChild				
						,"RemoveChild", &GameLogic::SceneUnitTransform::RemoveChild				
						,"ClearChildren", &GameLogic::SceneUnitTransform::ClearChildren				
						,"Deattach", &GameLogic::SceneUnitTransform::Deattach				
						,"CheckLoop", &GameLogic::SceneUnitTransform::CheckLoop				
						,"SetLocalPos", &GameLogic::SceneUnitTransform::SetLocalPos				
						,"GetLocalPos", &GameLogic::SceneUnitTransform::GetLocalPos				
						,"GetPos", &GameLogic::SceneUnitTransform::GetPos				
						,"SetFaceDir", &GameLogic::SceneUnitTransform::SetFaceDir				
						,"GetFaceDir", &GameLogic::SceneUnitTransform::GetFaceDir				
						,"SetFaceAngle", &GameLogic::SceneUnitTransform::SetFaceAngle				
						,"GetFaceAngle", &GameLogic::SceneUnitTransform::GetFaceAngle				
						,"CollectPBInit", &GameLogic::SceneUnitTransform::CollectPBInit				
						,"CollectPbMutable", &GameLogic::SceneUnitTransform::CollectPbMutable				
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
						ns_table.set(var_name, GameLogic::SceneUnitTransform::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}