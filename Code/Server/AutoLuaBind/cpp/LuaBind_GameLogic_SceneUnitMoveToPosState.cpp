#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveToPosState.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveToPosState(lua_State *L)
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
                std::string name = "SceneUnitMoveToPosState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveToPosState> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMoveToPosState(GameLogic::SceneUnitMove *)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMoveToPosState"; })				
						,"Enter", &GameLogic::SceneUnitMoveToPosState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveToPosState::Exit				
						,"Update", &GameLogic::SceneUnitMoveToPosState::Update				
						,"Flash", &GameLogic::SceneUnitMoveToPosState::Flash				
						,"IsDone", &GameLogic::SceneUnitMoveToPosState::IsDone				
						,"SetDesiredPos", &GameLogic::SceneUnitMoveToPosState::SetDesiredPos				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitMoveState 
						>()
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