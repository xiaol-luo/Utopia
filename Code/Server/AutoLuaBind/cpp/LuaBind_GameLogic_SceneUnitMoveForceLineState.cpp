#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Common/Utils/Ticker.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveForceLineState.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "Logic/ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveForceLineState(lua_State *L)
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
                std::string name = "SceneUnitMoveForceLineState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveForceLineState> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMoveForceLineState(GameLogic::SceneUnitMove *)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMoveForceLineState"; })				
						,"Enter", &GameLogic::SceneUnitMoveForceLineState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveForceLineState::Exit				
						,"Update", &GameLogic::SceneUnitMoveForceLineState::Update				
						,"IsDone", &GameLogic::SceneUnitMoveForceLineState::IsDone				
						,"ForceDone", &GameLogic::SceneUnitMoveForceLineState::ForceDone				
						,"Flash", &GameLogic::SceneUnitMoveForceLineState::Flash				
						,"ForceMoveLine", &GameLogic::SceneUnitMoveForceLineState::ForceMoveLine				
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