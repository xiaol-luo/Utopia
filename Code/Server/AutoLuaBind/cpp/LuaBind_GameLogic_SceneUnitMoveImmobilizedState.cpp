#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/Utils/Ticker.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveImmobilizedState.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveImmobilizedState(lua_State *L)
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
                std::string name = "SceneUnitMoveImmobilizedState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveImmobilizedState> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMoveImmobilizedState(GameLogic::SceneUnitMove *)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMoveImmobilizedState"; })				
						,"Enter", &GameLogic::SceneUnitMoveImmobilizedState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveImmobilizedState::Exit				
						,"Update", &GameLogic::SceneUnitMoveImmobilizedState::Update				
						,"IsDone", &GameLogic::SceneUnitMoveImmobilizedState::IsDone				
						,"ImmobilizeEndMs", &GameLogic::SceneUnitMoveImmobilizedState::ImmobilizeEndMs				
						,"GetEndTimestampMs", &GameLogic::SceneUnitMoveImmobilizedState::GetEndTimestampMs				
						,"ForceDone", &GameLogic::SceneUnitMoveImmobilizedState::ForceDone				
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