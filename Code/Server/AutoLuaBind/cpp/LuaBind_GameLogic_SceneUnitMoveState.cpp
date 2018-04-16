#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveState(lua_State *L)
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
                std::string name = "SceneUnitMoveState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveState> meta_table(
						"__StructName__", sol::property([]() {return "SceneUnitMoveState"; })				
						,"Enter", &GameLogic::SceneUnitMoveState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveState::Exit				
						,"Update", &GameLogic::SceneUnitMoveState::Update				
						,"IsDone", &GameLogic::SceneUnitMoveState::IsDone				
						,"ForceDone", &GameLogic::SceneUnitMoveState::ForceDone				
						,"Flash", &GameLogic::SceneUnitMoveState::Flash				
						,"GetState", &GameLogic::SceneUnitMoveState::GetState
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