#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveIdleState.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveIdleState(lua_State *L)
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
                std::string name = "SceneUnitMoveIdleState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveIdleState> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMoveIdleState(GameLogic::SceneUnitMove *)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMoveIdleState"; })				
						,"Enter", &GameLogic::SceneUnitMoveIdleState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveIdleState::Exit				
						,"Update", &GameLogic::SceneUnitMoveIdleState::Update				
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