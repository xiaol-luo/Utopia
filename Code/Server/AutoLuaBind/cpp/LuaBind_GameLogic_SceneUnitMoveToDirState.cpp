#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveToDirState.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveToDirState(lua_State *L)
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
                std::string name = "SceneUnitMoveToDirState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveToDirState> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMoveToDirState(GameLogic::SceneUnitMove *)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMoveToDirState"; })				
						,"Enter", &GameLogic::SceneUnitMoveToDirState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveToDirState::Exit				
						,"Update", &GameLogic::SceneUnitMoveToDirState::Update				
						,"Flash", &GameLogic::SceneUnitMoveToDirState::Flash				
						,"SetDesiredDir", &GameLogic::SceneUnitMoveToDirState::SetDesiredDir				
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