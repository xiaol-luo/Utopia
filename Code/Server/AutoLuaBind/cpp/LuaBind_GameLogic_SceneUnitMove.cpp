#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "ShareCode/Common/Utils/Ticker.h"	
#include "LogicModules/GameLogic/Scene/Navigation/NavAgent.h"	
#include "LogicModules/GameLogic/Scene/Navigation/NavMesh.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "ShareCode/Common/Geometry/Vector3.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMove(lua_State *L)
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
                std::string name = "SceneUnitMove";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMove> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMove()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMove"; })				
						,"UpdateState", &GameLogic::SceneUnitMove::UpdateState				
						,"SetPos", &GameLogic::SceneUnitMove::SetPos				
						,"GetPos", &GameLogic::SceneUnitMove::GetPos				
						,"GetVelocity", &GameLogic::SceneUnitMove::GetVelocity				
						,"SetVelocity", &GameLogic::SceneUnitMove::SetVelocity				
						,"GetNavAgent", &GameLogic::SceneUnitMove::GetNavAgent				
						,"GetNavMesh", &GameLogic::SceneUnitMove::GetNavMesh				
						,"CollectPBInit", &GameLogic::SceneUnitMove::CollectPBInit				
						,"CollectPbMutable", &GameLogic::SceneUnitMove::CollectPbMutable				
						,"CalMoveState", &GameLogic::SceneUnitMove::CalMoveState				
						,"GetMoveAgentState", &GameLogic::SceneUnitMove::GetMoveAgentState				
						,"GetMoveState", &GameLogic::SceneUnitMove::GetMoveState				
						,"IsLoseControl", &GameLogic::SceneUnitMove::IsLoseControl				
						,"TryMoveToPos", &GameLogic::SceneUnitMove::TryMoveToPos				
						,"TryMoveToDir", &GameLogic::SceneUnitMove::TryMoveToDir				
						,"CancelMove", &GameLogic::SceneUnitMove::CancelMove				
						,"CancelForceMove", &GameLogic::SceneUnitMove::CancelForceMove				
						,"ForceMoveLine", &GameLogic::SceneUnitMove::ForceMoveLine				
						,"ForcePos", &GameLogic::SceneUnitMove::ForcePos				
						,"ChangeForcePosDestination", &GameLogic::SceneUnitMove::ChangeForcePosDestination				
						,"Immobilized", &GameLogic::SceneUnitMove::Immobilized				
						,"CancelImmobilized", &GameLogic::SceneUnitMove::CancelImmobilized				
						,"Flash", &GameLogic::SceneUnitMove::Flash				
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
						ns_table.set(var_name, GameLogic::SceneUnitMove::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}